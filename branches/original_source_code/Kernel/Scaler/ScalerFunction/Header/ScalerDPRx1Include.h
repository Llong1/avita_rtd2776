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
// ID Code      : ScalerDPRx1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_D1_DP_EXIST == _ON)
//--------------------------------------------------
// Macro of DP Lane Mapping
//--------------------------------------------------
#define GET_DP_RX1_PCB_LANE0_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane0Mapping)
#define SET_DP_RX1_PCB_LANE0_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane0Mapping = (x))

#define GET_DP_RX1_PCB_LANE1_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane1Mapping)
#define SET_DP_RX1_PCB_LANE1_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane1Mapping = (x))

#define GET_DP_RX1_PCB_LANE2_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane2Mapping)
#define SET_DP_RX1_PCB_LANE2_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane2Mapping = (x))

#define GET_DP_RX1_PCB_LANE3_MAPPING()                  (g_stDpRx1LanesMapping.b2Lane3Mapping)
#define SET_DP_RX1_PCB_LANE3_MAPPING(x)                 (g_stDpRx1LanesMapping.b2Lane3Mapping = (x))

#define GET_DP_RX1_PCB_PN_SWAP()                        (g_stDpRx1LanesMapping.b1PNSwap)
#define SET_DP_RX1_PCB_PN_SWAP(x)                       (g_stDpRx1LanesMapping.b1PNSwap = (x))

//--------------------------------------------------
// Definitions of DP Lane Setting Ralation to Actual Lane Mapping
//--------------------------------------------------
#define _D1_DP_LANE0                                    (GET_DP_RX1_PCB_LANE0_MAPPING())
#define _D1_DP_LANE1                                    (GET_DP_RX1_PCB_LANE1_MAPPING())
#define _D1_DP_LANE2                                    (GET_DP_RX1_PCB_LANE2_MAPPING())
#define _D1_DP_LANE3                                    (GET_DP_RX1_PCB_LANE3_MAPPING())

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
//----------------------------------------------------------------------------
// Macro of Dp Link Training Information
//----------------------------------------------------------------------------
#define GET_DP_RX1_FAKE_LINK_TRAINING()                 ((g_ucDpRx1Info & _BIT7) >> 7)
#define SET_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info |= _BIT7)
#define CLR_DP_RX1_FAKE_LINK_TRAINING()                 (g_ucDpRx1Info &= ~_BIT7)

#define GET_DP_RX1_VALID_VIDEO_CHECK()                  ((g_ucDpRx1Info & _BIT6) >> 6)
#define SET_DP_RX1_VALID_VIDEO_CHECK()                  (g_ucDpRx1Info |= _BIT6)
#define CLR_DP_RX1_VALID_VIDEO_CHECK()                  (g_ucDpRx1Info &= ~_BIT6)

#define GET_DP_RX1_CRC_CALCULATE()                      ((g_ucDpRx1Info & _BIT5) >> 5)
#define SET_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info |= _BIT5)
#define CLR_DP_RX1_CRC_CALCULATE()                      (g_ucDpRx1Info &= ~_BIT5)

#define GET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle)
#define SET_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _TRUE)
#define CLR_DP_RX1_PS_AUX_TOGGLE()                      (g_bDpRx1PSAuxToggle = _FALSE)

// Add for DPCD 2002h Bug
#define GET_DP_RX1_POWER_STATE_INTO_PS()                (g_bDpRx1PowerStateIntoPS)
#define SET_DP_RX1_POWER_STATE_INTO_PS()                (g_bDpRx1PowerStateIntoPS = _TRUE)
#define CLR_DP_RX1_POWER_STATE_INTO_PS()                (g_bDpRx1PowerStateIntoPS = _FALSE)

#define GET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply)
#define SET_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _TRUE)
#define CLR_DP_RX1_AUX_COMMAND_NO_REPLY()               (g_bDpRx1AuxCommandNoReply = _FALSE)

#define GET_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount)
#define ADD_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount++)
#define CLR_DP_RX1_MSA_FAIL_MAC_RESET_COUNT()           (g_ucDpRx1MSAFailMacRsetCount = 0)

#define GET_DP_RX1_FORCE_BCKGRD_PATH()                  (g_enumDPRx1IrqForceBackgrd & _DISPLAY_PATH_ALL)
#define SET_DP_RX1_FORCE_BCKGRD_PATH(x)                 (g_enumDPRx1IrqForceBackgrd |= (x))
#define CLR_DP_RX1_FORCE_BCKGRD_PATH(x)                 (g_enumDPRx1IrqForceBackgrd &= ~(x))

#if(_DP_MST_SUPPORT == _ON)
#define GET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce)
#define SET_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce = _TRUE)
#define CLR_DP_RX1_CHECK_AUX_CH_NO_POWER_DEBOUNCE()     (g_stDpRx1MiscInfo.b1DpCheckAuxChNoPowerDebounce = _FALSE)

#define GET_DP_RX1_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx1MiscInfo.b1DpCheckAuxChPowerOff)
#define SET_DP_RX1_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx1MiscInfo.b1DpCheckAuxChPowerOff = _TRUE)
#define CLR_DP_RX1_CHECK_AUX_CH_POWER_OFF()             (g_stDpRx1MiscInfo.b1DpCheckAuxChPowerOff = _FALSE)

#define GET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp)
#define SET_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp = _TRUE)
#define CLR_DP_RX1_AUX_CH_POWER_ON_WAKE_UP()            (g_stDpRx1MiscInfo.b1DpAuxChPowerOnWakeUp = _FALSE)

#define GET_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn)
#define SET_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn = _TRUE)
#define CLR_DP_RX1_SOURCE_FIRST_POWER_ON()              (g_stDpRx1MiscInfo.b1DpSourceFirstPowerOn = _FALSE)

#define GET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx1BackupLinkStatusFlg_INT)
#define SET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx1BackupLinkStatusFlg_INT = _TRUE)
#define CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG()          (g_bDpMSTRx1BackupLinkStatusFlg_INT = _FALSE)
#endif // #if(_DP_MST_SUPPORT == _ON)

#define SET_DP_RX1_AUX_MANUAL_MODE_EXINT()              {\
                                                            for(g_ucRx1AuxTemp_EXINT = 0; ((ScalerGetBit_EXINT(PBA_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx1AuxTemp_EXINT < 255)); g_ucRx1AuxTemp_EXINT++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                        }

#define SET_DP_RX1_AUX_MANUAL_MODE()                    {\
                                                            EX0 = 0;\
                                                            for(g_ucRx1AuxTemp = 0; ((ScalerGetBit(PBA_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx1AuxTemp < 255)); g_ucRx1AuxTemp++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);\
                                                            EX0 = 1;\
                                                        }


#define SET_DP_RX1_AUX_AUTO_MODE_EXINT()                {\
                                                            for(g_ucRx1AuxTemp_EXINT = 0; ((ScalerGetBit_EXINT(PBA_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx1AuxTemp_EXINT < 255)); g_ucRx1AuxTemp_EXINT++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                        }

#define SET_DP_RX1_AUX_AUTO_MODE()                      {\
                                                            EX0 = 0;\
                                                            for(g_ucRx1AuxTemp = 0; ((ScalerGetBit(PBA_C7_TP1_OCCR, 0x07) >= 0x02) && (g_ucRx1AuxTemp < 255)); g_ucRx1AuxTemp++)\
                                                            {\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                                _nop_();\
                                                            }\
                                                            ScalerSetBit(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);\
                                                            EX0 = 1;\
                                                        }

#define GET_DP_RX1_VFRONT_PORCH()                       (g_usDpRx1Vfrontporch)
#define SET_DP_RX1_VFRONT_PORCH(x)                      (g_usDpRx1Vfrontporch = (x))

#define SET_DP_RX1_PORCH_COLOR_RGB()                    {\
                                                            ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x00);\
                                                            ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                            ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x00);\
                                                            ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                            ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x00);\
                                                            ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_LIMIT(X)             {\
                                                            if(GET_COLOR_SPACE(X) == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x0F);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#define SET_DP_RX1_PORCH_COLOR_YCC_FULL(X)              {\
                                                            if(GET_COLOR_SPACE(X) == _COLOR_SPACE_YCBCR420)\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x10);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x10);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                            else\
                                                            {\
                                                                ScalerSetByte(PB8_51_MN_DPF_BG_RED_M, 0x80);\
                                                                ScalerSetByte(PB8_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PB8_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PB8_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PB8_55_MN_DPF_BG_BLU_M, 0x80);\
                                                                ScalerSetByte(PB8_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }\
                                                        }

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#define GET_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode)
#define SET_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode = _TRUE)
#define CLR_DP_RX1_VSC_SDP_COLOR_MODE()                 (g_bDpRx1VscSdpColorMode = _FALSE)

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
#define GET_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting)
#define SET_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting = _TRUE)
#define CLR_DP_RX1_RSV1_DETECTING()                     (g_bDpRx1RSV1PacketDetecting = _FALSE)

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
#define GET_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting)
#define SET_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting = _TRUE)
#define CLR_DP_RX1_MST2SST_RSV1_DETECTING()             (g_bDpRx1MstToSstRSV1PacketDetecting = _FALSE)
#endif
#endif
#endif

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Macro of RX HDCP Authentication
//--------------------------------------------------
#define GET_DP_RX1_HDCP_AUTH_STATE()                    (g_stDpRx1HDCPAuthInfo.b4AuthState)
#define SET_DP_RX1_HDCP_AUTH_STATE(x)                   (g_stDpRx1HDCPAuthInfo.b4AuthState = (x))

#define GET_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange)
#define SET_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_STATE_CHANGE()             (g_stDpRx1HDCPAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout)
#define SET_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_REPEATER_PROC_TIMEOUT()    (g_stDpRx1HDCPAuthInfo.b1AuthRepeaterProcTimeout = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout)
#define SET_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_READ_IRQ_TIMEOUT()         (g_stDpRx1HDCPAuthInfo.b1AuthReadIrqTimeout = _FALSE)

#define GET_DP_RX1_HDCP_UPSTREAM_EVENT()                (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent)
#define SET_DP_RX1_HDCP_UPSTREAM_EVENT(x)               (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent = (x))
#define CLR_DP_RX1_HDCP_UPSTREAM_EVENT()                (g_stDpRx1HDCPAuthInfo.ucAuthUpstreamEvent = _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_NONE)

#define GET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer)
#define SET_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_CPIRQ_TIMRE()              (g_stDpRx1HDCPAuthInfo.b1AuthCpIrqTimer = _FALSE)

#define GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten)
#define SET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten = _TRUE)
#define CLR_DP_RX1_HDCP_AUTH_AKSV_WRITTEN()             (g_bDpRx1HdcpAksvWritten = _FALSE)

#define GET_DP_RX1_HDCP_REPEATER_SUPPORT()              ((ScalerDpRx1GetDpcdInfo(0x06, 0x80, 0x28) & (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))

#define GET_DP_RX1_MST_TO_SST_VFRONT_PORCH()            (g_usDpRx1MstToSstVfrontporch)
#define SET_DP_RX1_MST_TO_SST_VFRONT_PORCH(x)           (g_usDpRx1MstToSstVfrontporch = (x))
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
#define GET_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting)
#define SET_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _TRUE)
#define CLR_DP_RX1_RSV0_DETECTING()                     (g_stDPRx1InfoFrameRSV0Ctrl.b1RSV0PacketDetecting = _FALSE)

#define GET_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive)
#define SET_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_HDR_INFO_FRAME_RECEIVED()            (g_stDPRx1InfoFrameRSV0Ctrl.b1HDRInfoFrameReceive = _FALSE)

#define GET_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx1InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive)
#define SET_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx1InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_FREESYNC_INFO_FRAME_RECEIVED()       (g_stDPRx1InfoFrameRSV0Ctrl.b1FreesyncInfoFrameReceive = _FALSE)

#define GET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive)
#define SET_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _TRUE)
#define CLR_DP_RX1_AUDIO_INFO_FRAME_RECEIVED()          (g_stDPRx1InfoFrameRSV0Ctrl.b1AudioInfoFrameReceive = _FALSE)
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern BYTE g_ucDpRx1Temp;
extern bit g_bDpRx1PSAuxToggle;

// Add for DPCD 2002h Bug
extern bit g_bDpRx1PowerStateIntoPS;
extern bit g_bDpRx1AuxCommandNoReply;

extern BYTE g_ucDpRx1Info;
extern BYTE g_ucDpRx1LinkRate;
extern BYTE g_ucDpRx1LaneCount;
extern BYTE g_ucDpRx1TrainingPatternSet;
extern BYTE g_ucRx1AuxTemp;
extern BYTE g_ucRx1AuxTemp_EXINT;
extern WORD g_usDpRx1Vfrontporch;
extern EnumDisplayDataPath g_enumDPRx1IrqForceBackgrd;
extern StructDpLanesMapping g_stDpRx1LanesMapping;

#if(_DP_MST_SUPPORT == _ON)
extern StructDPRxMiscInfo g_stDpRx1MiscInfo;
extern bit g_bDpMSTRx1BackupLinkStatusFlg_INT;
extern BYTE g_pucDpRx1LinkStatusBackup_INT[2];
#endif

#if(_DP_TX_SUPPORT == _ON)
extern bit g_bDpRx1HdcpAksvWritten;
extern StructDPRxHDCPAuthInfo g_stDpRx1HDCPAuthInfo;
extern WORD g_usDpRx1MstToSstVfrontporch;
#endif

#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern BYTE g_pucDPRx1Caps[3];
#endif

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpRx1VscSdpColorMode;

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern bit g_bDpRx1RSV1PacketDetecting;

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))
extern bit g_bDpRx1MstToSstRSV1PacketDetecting;
#endif
#endif
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern BYTE g_pucDPRx1HDRBackup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern BYTE g_pucDPRx1RSV0Backup[_HW_DP_INFOFRAME_RSV0_LENGTH];
extern StructDPInfoFrameRSV0Ctrl g_stDPRx1InfoFrameRSV0Ctrl;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpRx1SetDpLaneMapping(BYTE ucLanetype);
extern void ScalerDpRx1ChangeDpcdVersion(EnumDpVersionType enumDpVersion, EnumDPMSTPort enumDpRxMstPort);
extern void ScalerDpRx1DpcdLinkStatusReset(EnumDpResetStatus enumDpResetStatus);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx1DpcdLinkStatusReset_WDINT(void);
#endif

extern void ScalerDpRx1HotPlugEvent(EnumDpHotPlugAssertType enumHpdType);
extern bit ScalerDpRx1MarginLinkCheck(void);
extern void ScalerDpRx1LinkStatusIRQ(void);
extern void ScalerDpRx1HotPlugDuration(WORD usMs);
extern void ScalerDpRx1MacInitial(void);
extern void ScalerDpRx1SecDataBlockReset(void);
extern BYTE ScalerDpRx1TrainingPattern1_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern BYTE ScalerDpRx1TrainingPattern2_EXINT0(EnumDpLinkTrainingType enumDpLtType);
extern void ScalerDpRx1TrainingPatternEnd_EXINT0(void);
extern bit ScalerDpRx1AlignCheck(void);
extern bit ScalerDpRx1DecodeCheck(void);
extern bit ScalerDpRx1SignalCheck(BYTE ucDpLinkRate, BYTE ucDpcdLane);
extern BYTE ScalerDpRx1DFECheck_EXINT0(void);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern BYTE ScalerDpRx1DFECheck_WDINT(void);
#endif

extern bit ScalerDpRx1MSACheck(void);
extern bit ScalerDpRx1MiscCheck(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit ScalerDpRx1VscCheck(void);

#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx1RSV1PacketDetectEvent(void);
extern void ScalerDpRx1SetInitialRSV1InfoType(void);
#endif
#endif
extern void ScalerDpRx1AVMute(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1UpdateSinkCount(void);
#endif

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx1WDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID);
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
extern WORD ScalerDpRx1GetBStoHSDelay(WORD usDpHtotal);
extern WORD ScalerDpRx1GetVFreq(void);
extern WORD ScalerDpRx1GetVPeriod(void);
extern WORD ScalerDpRx1GetHPeriod(void);
extern WORD ScalerDpRx1GetHSW(void);
extern BYTE ScalerDpRx1GetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
extern BYTE ScalerDpRx1GetAmdSpdBackupInfo(EnumAmdSpdInfoContent enumContent);
#endif

#if(_ULTRA_HDR_SUPPORT == _ON)
extern void ScalerDpRx1InfoFrameRSV0Check(void);
extern void ScalerDpRx1RSV0PacketDetectEvent(void);
#endif

extern void ScalerDpRx1SetInitialRSV0InfoType(void);
extern DWORD ScalerDpRx1GetBStoVSDelay(void);
extern bit ScalerDpRx1InterlaceCheck(WORD *pusVTotal, BYTE *pucOddFlg);
extern bit ScalerDpRx1GetVideoInfo(void);
extern void ScalerDpRx1SetColorInfo(void);
extern void ScalerDpRx1VideoSetting(void);
extern void ScalerDpRx1ColorimetrySetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern void ScalerDpRx1ColorimetryExtSetting(BYTE ucInputPort, BYTE ucColorimetryValue);
#endif
extern void ScalerDpRx1QuantizationSetting(BYTE ucInputPort, BYTE ucQuantizationValue);

extern bit ScalerDpRx1StreamClkRegenerate(void);
extern void ScalerDpRx1AdjustVsyncDelay(void);
extern void ScalerDpRx1SinkStatusSet(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx1SinkStatusSet_EXINT0(EnumDpSinkReceivePort enumReceiverPort, EnumDpSinkStatus enumInSync);
extern void ScalerDpRx1CrcCalculate(void);
#if(_HW_HS_TRACKING_GEN_TYPE == _HS_TRACKING_GEN_2)
void ScalerDpRx1HSActiveTrackingMode(EnumDpHSTrackingType enumHSTrackingType);
#endif
extern void ScalerDpRx1CheckHdcpCpirqStatus(void);
extern bit ScalerDpRx1HdcpCheck(void);
extern bit ScalerDpRx1HdcpReAuthStatusCheck(void);
extern void ScalerDpRx1CpIRQ(EnumDpRxBStatusType enumBStatusType);
extern bit ScalerDpRx1HdcpEnebled(void);
extern BYTE ScalerDpRx1GetDpcdInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpRx1GetDpcdBitInfo(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern BYTE ScalerDpRx1GetDpcdInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL);
extern BYTE ScalerDpRx1GetDpcdBitInfo_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdBit);
extern void ScalerDpRx1SetDpcdValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx1SetDpcdBitValue(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);
extern void ScalerDpRx1SetDpcdValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
extern void ScalerDpRx1SetDpcdBitValue_EXINT0(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucNotDpcdBit, BYTE ucDpcdBit);

#if(_WD_TIMER_INT_SUPPORT == _ON)
extern void ScalerDpRx1SetDpcdValue_WDINT(BYTE ucDpcdAccessPortH, BYTE ucDpcdAccessPortM, BYTE ucDpcdAccessPortL, BYTE ucDpcdValue);
#endif

extern bit ScalerDpRx1NormalPreDetect(void);
extern BYTE ScalerDpRx1ScanInputPort(void);
extern bit ScalerDpRx1PSPreDetect(void);
extern bit ScalerDpRx1StableDetect(void);
extern void ScalerDpRx1HPDPowerOfftoNormalProc(BYTE ucDpHotPlugDCOffHighStatus);
extern bit ScalerDpRx1CheckVgipVsBypass(void);

#if(_DP_MST_SUPPORT == _ON)
extern bit ScalerDpRx1LTStatusCheck(void);
extern void ScalerDpRx1MstInfoBackup(EnumDpMstBackup enumDpMstBackup);
extern void ScalerDpRx1MstReset(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1HDCPSetRepeaterProcTimeout(void);
extern void ScalerDpRx1HDCPSetReadIrqTimeout(void);
extern void ScalerDpRx1HDCPAuthShaRun(bit bIsFirst);

#if(_D1_DP_MST_PORT_SUPPORT == _ON)
extern void ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0(void);
extern void ScalerDpRx1HDCPSetKsvFifo_EXINT0(void);
extern void ScalerDpRx1HDCPResetDpcdInfo_EXINT0(void);
extern void ScalerDpRx1HDCPBlockReset(void);
#endif

extern bit ScalerDpRx1HDCPCheckLvp(void);

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#if(_HW_DP_VSC_SDP_REG_SUPPORT != _ON)
extern void ScalerDpRx1MstToSstRSV1PacketDetectEvent(void);
#endif
#endif
#endif
#endif

extern bit ScalerDpRx1ValidSignalDetectionDCOnCheck(void);

#if(_DP_TX_SUPPORT == _ON)
extern void ScalerDpRx1MstToSstProc(void);
extern void ScalerDpRx1MstToSstSetColorInfo(void);
#endif

#endif // End of #if(_D1_DP_EXIST == _ON)

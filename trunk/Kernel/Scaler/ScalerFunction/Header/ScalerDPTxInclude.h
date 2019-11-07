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
// ID Code      : ScalerDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// DownStream Port Type
//--------------------------------------------------
#define _DP_TYPE                                            0
#define _VGA_TYPE                                           1
#define _DVI_TYPE                                           2
#define _OTHER_TYPE                                         3

//--------------------------------------------------
// Peer Deveice Type
//--------------------------------------------------
#define _DP_NO_DEVICE                                       0
#define _DP_SOURCE_OR_SST_BRANCH_UPSTREAM                   1
#define _DP_MST_OR_SST_BRANCH_DOWNSTREAM                    2
#define _DP_SST_SINK                                        3
#define _DP_TO_LEGACY                                       4

//--------------------------------------------------
// MST Status
//--------------------------------------------------
#define _DP_MSG_NO_SUPPORT                                  0
#define _DP_MSG_SUPPORT                                     1


#define _DP_TX_SSC_30K                                      30
#define _DP_TX_SSC_32K                                      32
#define _DP_TX_SSC_33K                                      33
#define _DP_TX_SSC_FREQ                                     _DP_TX_SSC_32K


#define _DP_TX_AUX_DIFF_MODE                                0
#define _DP_TX_AUX_SINGLE_MODE                              1

//--------------------------------------------------
// HDCP Info
//--------------------------------------------------
#define _DP_TX_HDCP_DEVICE_COUNT_MAX                        127
#define _DP_TX_LINK_CLK_MHZ                                 (WORD) ((GET_DP_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_RBR) ? 162 : ((GET_DP_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_HBR) ? 270 : 540))

#define GET_DP_TX_HPD_DEBOUNCE_LEVEL()                      (ScalerGetBit(PBB_70_HPD_CTRL, _BIT2) >> 2)


#define GET_DP_TX_MODE_STATE()                              (g_stTxModeInfo.b3ModeState)
#define SET_DP_TX_MODE_STATE(x)                             (g_stTxModeInfo.b3ModeState = (x))

#define GET_DP_TX_MODE_STATE_CHANGE()                       (g_stTxModeInfo.b1ModeStateChanged)
#define SET_DP_TX_MODE_STATE_CHANGE()                       (g_stTxModeInfo.b1ModeStateChanged = _TRUE)
#define CLR_DP_TX_MODE_STATE_CHANGE()                       (g_stTxModeInfo.b1ModeStateChanged = _FALSE)

#define GET_DP_TX_HPD_EVENT()                               (g_stTxModeInfo.b2HPDEvent)
#define SET_DP_TX_HPD_EVENT(x)                              (g_stTxModeInfo.b2HPDEvent = (x))

#define GET_DP_TX_HPD_FIRST_PLUG()                          (g_stTxModeInfo.b1FirstHPD)
#define SET_DP_TX_HPD_FIRST_PLUG()                          (g_stTxModeInfo.b1FirstHPD = _TRUE)
#define CLR_DP_TX_HPD_FIRST_PLUG()                          (g_stTxModeInfo.b1FirstHPD = _FALSE)

#define GET_DP_TX_FORCE_LINK_TRAINING()                     (g_stTxModeInfo.b1ForceLT)
#define SET_DP_TX_FORCE_LINK_TRAINING()                     (g_stTxModeInfo.b1ForceLT = _TRUE)
#define CLR_DP_TX_FORCE_LINK_TRAINING()                     (g_stTxModeInfo.b1ForceLT = _FALSE)

#define GET_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_stTxModeInfo.b1ExceedBandwidth)
#define SET_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_stTxModeInfo.b1ExceedBandwidth = _TRUE)
#define CLR_DP_TX_EXCEED_LINK_BANDWIDTH()                   (g_stTxModeInfo.b1ExceedBandwidth = _FALSE)

#define GET_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpTxIRQHPDDetected)
#define SET_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpTxIRQHPDDetected = _TRUE)
#define CLR_DP_TX_IRQ_HPD_DETECTED()                        (g_bDpTxIRQHPDDetected = _FALSE)

#define GET_DP_TX_IRQ_HPD_TYPE(x)                           (g_enumDpTxIRQType & (x))
#define SET_DP_TX_IRQ_HPD_TYPE(x)                           (g_enumDpTxIRQType |= (x))
#define CLR_DP_TX_IRQ_HPD_TYPE()                            (g_enumDpTxIRQType &= 0x00)
#define CLR_DP_TX_IRQ_HPD_TARGET_TYPE(x)                    (g_enumDpTxIRQType &= ~(x))

#define GET_DP_TX_IRQ_HPD_TYPE_INT()                        (g_enumDpTxIRQTypeInt)
#define SET_DP_TX_IRQ_HPD_TYPE_INT(x)                       (g_enumDpTxIRQTypeInt |= (x))
#define CLR_DP_TX_IRQ_HPD_TYPE_INT()                        (g_enumDpTxIRQTypeInt &= 0x00)

#define GET_DP_TX_IRQ_HDCP_TYPE(x)                          (g_enumDpTxIRQHDCPType & (x))
#define SET_DP_TX_IRQ_HDCP_TYPE(x)                          (g_enumDpTxIRQHDCPType |= (x))
#define CLR_DP_TX_IRQ_HDCP_TYPE()                           (g_enumDpTxIRQHDCPType &= 0x00)
#define CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(x)                   (g_enumDpTxIRQHDCPType &= ~(x))

#define GET_DP_TX_HPD_STATUS_CHANGE()                       (ScalerGetBit(PBB_71_HPD_IRQ, (_BIT6 | _BIT4)) != 0x00)

//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#define GET_DP_TX_DOWNSTREAM_DPCD_REV()                     (g_stDownStreamInfo.ucDPCDRev)
#define SET_DP_TX_DOWNSTREAM_DPCD_REV(x)                    (g_stDownStreamInfo.ucDPCDRev = (x))

#define GET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE()              (g_stDownStreamInfo.b3PeerDeviceType)
#define SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(x)             (g_stDownStreamInfo.b3PeerDeviceType = (x))

#define GET_DP_TX_DOWNSTREAM_LINK_RATE()                    (g_stDownStreamInfo.ucLinkRate)
#define SET_DP_TX_DOWNSTREAM_LINK_RATE(x)                   (g_stDownStreamInfo.ucLinkRate = (x))

#define GET_DP_TX_DOWNSTREAM_LANE_NUM()                     (g_stDownStreamInfo.b3LaneNum)
#define SET_DP_TX_DOWNSTREAM_LANE_NUM(x)                    (g_stDownStreamInfo.b3LaneNum = (x))

#define GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS()                (g_stDownStreamInfo.b1MSGCapStatus)
#define SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(x)               (g_stDownStreamInfo.b1MSGCapStatus = (x))

#define GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS()                (g_stDownStreamInfo.b1DPPlugStatus)
#define SET_DP_TX_DOWNSTREAM_DPPLUG_STATUS(x)               (g_stDownStreamInfo.b1DPPlugStatus = (x))

#define GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS()        (g_stDownStreamInfo.b1UpRequestCap)
#define SET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS(x)       (g_stDownStreamInfo.b1UpRequestCap = (x))

#define GET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE()                (g_stDownStreamInfo.b1DPPlugChange)
#define SET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE()                (g_stDownStreamInfo.b1DPPlugChange = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_DPPLUG_CHANGE()                (g_stDownStreamInfo.b1DPPlugChange = _FALSE)

#define GET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS()            (g_stDownStreamInfo.b1LegacyPlugStatus)
#define SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(x)           (g_stDownStreamInfo.b1LegacyPlugStatus = (x))

#define GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE()                (g_stDownStreamInfo.ucMaxLinkRate)
#define SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(x)               (g_stDownStreamInfo.ucMaxLinkRate = (x))

#define GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM()                 (g_stDownStreamInfo.b5MaxLaneNum)
#define SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM(x)                (g_stDownStreamInfo.b5MaxLaneNum = (x))

#define GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP()            (g_stDownStreamInfo.b5MaxLaneNumTemp)
#define SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(x)           (g_stDownStreamInfo.b5MaxLaneNumTemp = (x))

#define GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING()              (g_stDownStreamInfo.b1EnhanceFraming)
#define SET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING(x)             (g_stDownStreamInfo.b1EnhanceFraming = (x))

#define GET_DP_TX_DOWNSTREAM_DOWN_SPREAD()                  (g_stDownStreamInfo.b1SSCSupport)
#define SET_DP_TX_DOWNSTREAM_DOWN_SPREAD(x)                 (g_stDownStreamInfo.b1SSCSupport = (x))

#define GET_DP_TX_DOWNSTREAM_TP3_SUPPORT()                  (g_stDownStreamInfo.b1TP3Support)
#define SET_DP_TX_DOWNSTREAM_TP3_SUPPORT()                  (g_stDownStreamInfo.b1TP3Support = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_TP3_SUPPORT()                  (g_stDownStreamInfo.b1TP3Support = _FALSE)

#define GET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP()                (g_stDownStreamInfo.b1NumberOfSDP)
#define SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP(x)               (g_stDownStreamInfo.b1NumberOfSDP = (x))

#define GET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK()           (g_stDownStreamInfo.b1NumberOfSDPSink)
#define SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(x)          (g_stDownStreamInfo.b1NumberOfSDPSink = (x))

#define GET_DP_TX_DOWNSTREAM_INFO_READY()                   (g_stDownStreamInfo.b1DownStreamInfoReady)
#define SET_DP_TX_DOWNSTREAM_INFO_READY()                   (g_stDownStreamInfo.b1DownStreamInfoReady = _TRUE)
#define CLR_DP_TX_DOWNSTREAM_INFO_READY()                   (g_stDownStreamInfo.b1DownStreamInfoReady = _FALSE)

//--------------------------------------------------
// Macros of DP Tx Input Infomation
//--------------------------------------------------
#define GET_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpTxSourceChanged)
#define SET_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpTxSourceChanged = _TRUE)
#define CLR_DP_TX_STREAM_SOURCE_CHANGE()                    (g_bDpTxSourceChanged = _FALSE)

#define GET_DP_TX_STREAM_SOURCE()                           (g_ucDpTxStreamSource)
#define SET_DP_TX_STREAM_SOURCE(x)                          (g_ucDpTxStreamSource = (x))

#define GET_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stTxInputInfo.b1AudioReadyToPlay)
#define SET_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stTxInputInfo.b1AudioReadyToPlay = _TRUE)
#define CLR_DP_TX_AUDIO_READY_TO_PLAY()                     (g_stTxInputInfo.b1AudioReadyToPlay = _FALSE)

#define GET_DP_TX_CURRENT_AUDIO_FREQUENCY()                 (g_stTxInputInfo.ucCurrnetAudioFrequency)
#define SET_DP_TX_CURRENT_AUDIO_FREQUENCY(x)                (g_stTxInputInfo.ucCurrnetAudioFrequency = (x))
#define CLR_DP_TX_CURRENT_AUDIO_FREQUENCY()                 (g_stTxInputInfo.ucCurrnetAudioFrequency = _DP_TX_AUDIO_FREQ_NO_AUDIO)

#define GET_DP_TX_AUDIO_CHANNEL_COUNT()                     (g_stTxInputInfo.b3AudioChannelCount)
#define SET_DP_TX_AUDIO_CHANNEL_COUNT(x)                    (g_stTxInputInfo.b3AudioChannelCount = (x))

#define GET_DP_TX_INPUT_COLOR_DEPTH()                       (g_stTxInputInfo.b3ColorDepth)
#define SET_DP_TX_INPUT_COLOR_DEPTH(x)                      (g_stTxInputInfo.b3ColorDepth = (x))

#define GET_DP_TX_INPUT_COLOR_SPACE()                       (g_stTxInputInfo.b3ColorSpace)
#define SET_DP_TX_INPUT_COLOR_SPACE(x)                      (g_stTxInputInfo.b3ColorSpace = (x))

#define GET_DP_TX_INPUT_PIXEL_CLK()                         (g_stTxInputInfo.usInputPixelClk)
#define SET_DP_TX_INPUT_PIXEL_CLK(x)                        (g_stTxInputInfo.usInputPixelClk = (x))
#define CLR_DP_TX_INPUT_PIXEL_CLK()                         (g_stTxInputInfo.usInputPixelClk = 0)

#define GET_DP_TX_INPUT_INTERLACE_MODE()                    (g_stTxInputInfo.b1InterlaceMode)
#define SET_DP_TX_INPUT_INTERLACE_MODE(x)                   (g_stTxInputInfo.b1InterlaceMode = (x))

#define GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER()           (g_stTxInputInfo.b1InterlaceVTotalNumber)
#define SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(x)          (g_stTxInputInfo.b1InterlaceVTotalNumber = (x))

#define GET_DP_TX_HORIZONTAL_DE_PERIOD()                    (g_stTxInputInfo.usHorizontalDataEnablePeriod)
#define SET_DP_TX_HORIZONTAL_DE_PERIOD(x)                   (g_stTxInputInfo.usHorizontalDataEnablePeriod = (x))

#define SET_DP_TX_PORCH_COLOR_RGB()                         {\
                                                                ScalerSetByte(PA_50_MN_DPF_BG_RED_M, 0x00);\
                                                                ScalerSetByte(PA_51_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PA_52_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PA_53_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PA_54_MN_DPF_BG_BLU_M, 0x00);\
                                                                ScalerSetByte(PA_55_MN_DPF_BG_BLU_L, 0x00);\
                                                            }

#define SET_DP_TX_PORCH_COLOR_YCC_LIMIT()                   {\
                                                                if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                {\
                                                                    ScalerSetByte(PA_50_MN_DPF_BG_RED_M, 0x10);\
                                                                    ScalerSetByte(PA_51_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetByte(PA_52_MN_DPF_BG_GRN_M, 0x10);\
                                                                    ScalerSetByte(PA_53_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetByte(PA_54_MN_DPF_BG_BLU_M, 0x80);\
                                                                    ScalerSetByte(PA_55_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetByte(PA_50_MN_DPF_BG_RED_M, 0x80);\
                                                                    ScalerSetByte(PA_51_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetByte(PA_52_MN_DPF_BG_GRN_M, 0x0F);\
                                                                    ScalerSetByte(PA_53_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetByte(PA_54_MN_DPF_BG_BLU_M, 0x80);\
                                                                    ScalerSetByte(PA_55_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#define SET_DP_TX_PORCH_COLOR_YCC_FULL()                    {\
                                                                if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR420)\
                                                                {\
                                                                    ScalerSetByte(PA_50_MN_DPF_BG_RED_M, 0x10);\
                                                                    ScalerSetByte(PA_51_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetByte(PA_52_MN_DPF_BG_GRN_M, 0x10);\
                                                                    ScalerSetByte(PA_53_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetByte(PA_54_MN_DPF_BG_BLU_M, 0x80);\
                                                                    ScalerSetByte(PA_55_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetByte(PA_50_MN_DPF_BG_RED_M, 0x80);\
                                                                    ScalerSetByte(PA_51_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetByte(PA_52_MN_DPF_BG_GRN_M, 0x00);\
                                                                    ScalerSetByte(PA_53_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetByte(PA_54_MN_DPF_BG_BLU_M, 0x80);\
                                                                    ScalerSetByte(PA_55_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
#define GET_DP_TX_VSC_SDP_COLOR_MODE()                      (g_bDpTxVscSdpColorMode)
#define SET_DP_TX_VSC_SDP_COLOR_MODE()                      (g_bDpTxVscSdpColorMode = _TRUE)
#define CLR_DP_TX_VSC_SDP_COLOR_MODE()                      (g_bDpTxVscSdpColorMode = _FALSE)
#endif

//--------------------------------------------------
// Macros of DP Tx Link Infomation
//--------------------------------------------------
#define GET_DP_TX_LT_STATE()                                (g_stTxLTInfo.b2LinkTrainingState)
#define SET_DP_TX_LT_STATE(x)                               (g_stTxLTInfo.b2LinkTrainingState = (x))

#define GET_DP_TX_LT_RESULT()                               (g_stTxLTInfo.b4LinkTrainingResult)
#define SET_DP_TX_LT_RESULT(x)                              (g_stTxLTInfo.b4LinkTrainingResult = (x))

#define GET_DP_TX_LINK_PBN_PER_TIMESOLT()                   (g_stTxLTInfo.ucLinkPBNPerTimeSlot)
#define SET_DP_TX_LINK_PBN_PER_TIMESOLT(x)                  (g_stTxLTInfo.ucLinkPBNPerTimeSlot = (x))

#define GET_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane0SameVolCnt)
#define ADD_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane0SameVolCnt++)
#define CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane0SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane1SameVolCnt)
#define ADD_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane1SameVolCnt++)
#define CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane1SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane2SameVolCnt)
#define ADD_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane2SameVolCnt++)
#define CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane2SameVolCnt = 0)

#define GET_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane3SameVolCnt)
#define ADD_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane3SameVolCnt++)
#define CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stTxLTInfo.b3TP1Lane3SameVolCnt = 0)

#define GET_DP_TX_TP2_CNT()                                 (g_stTxLTInfo.b3TP2count)
#define ADD_DP_TX_TP2_CNT()                                 (g_stTxLTInfo.b3TP2count++)
#define CLR_DP_TX_TP2_CNT()                                 (g_stTxLTInfo.b3TP2count = 0)

#define GET_DP_TX_LANE0_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane0Adjust & 0x03)
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane0Adjust = ((g_stTxLTInfo.ucLane0Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DP_TX_LANE1_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane1Adjust & 0x03)
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane1Adjust = ((g_stTxLTInfo.ucLane1Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DP_TX_LANE2_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane2Adjust & 0x03)
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane2Adjust = ((g_stTxLTInfo.ucLane2Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DP_TX_LANE3_CURRENT_VOL_SWING()                 (g_stTxLTInfo.ucLane3Adjust & 0x03)
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING(x)                (g_stTxLTInfo.ucLane3Adjust = ((g_stTxLTInfo.ucLane3Adjust & 0xFC) | (x)))
#define SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stTxLTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane0Adjust = ((g_stTxLTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane1Adjust = ((g_stTxLTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane2Adjust = ((g_stTxLTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()              ((g_stTxLTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(x)             (g_stTxLTInfo.ucLane3Adjust = ((g_stTxLTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stTxLTInfo.ucLane3Adjust &= ~_BIT5)

#define GET_DP_TX_LANE0_CR_DONE()                           ((g_stTxLTInfo.ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DP_TX_LANE1_CR_DONE()                           ((g_stTxLTInfo.ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DP_TX_LANE2_CR_DONE()                           ((g_stTxLTInfo.ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DP_TX_LANE3_CR_DONE()                           ((g_stTxLTInfo.ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DP_TX_LANE0_EQ_DONE()                           ((g_stTxLTInfo.ucLane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DP_TX_LANE1_EQ_DONE()                           ((g_stTxLTInfo.ucLane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_DP_TX_LANE2_EQ_DONE()                           ((g_stTxLTInfo.ucLane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DP_TX_LANE3_EQ_DONE()                           ((g_stTxLTInfo.ucLane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_DP_TX_LANE_ALIGN_DONE()                         ((g_stTxLTInfo.ucLaneAlignStatus & _BIT0) == _BIT0)


#define GET_DP_TX_LANE0_ADJUST_VOL_SWING()                  (g_stTxLTInfo.ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DP_TX_LANE0_ADJUST_VOL_SWING(x)                 (g_stTxLTInfo.ucAdjustReqLane01 = ((g_stTxLTInfo.ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE1_ADJUST_VOL_SWING()                  ((g_stTxLTInfo.ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE1_ADJUST_VOL_SWING(x)                 (g_stTxLTInfo.ucAdjustReqLane01 = ((g_stTxLTInfo.ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DP_TX_LANE2_ADJUST_VOL_SWING()                  (g_stTxLTInfo.ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DP_TX_LANE2_ADJUST_VOL_SWING(x)                 (g_stTxLTInfo.ucAdjustReqLane23 = ((g_stTxLTInfo.ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DP_TX_LANE3_ADJUST_VOL_SWING()                  ((g_stTxLTInfo.ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DP_TX_LANE3_ADJUST_VOL_SWING(x)                 (g_stTxLTInfo.ucAdjustReqLane23 = ((g_stTxLTInfo.ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()               ((g_stTxLTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define SET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS(x)              (g_stTxLTInfo.ucAdjustReqLane01 = ((g_stTxLTInfo.ucAdjustReqLane01 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()               ((g_stTxLTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define SET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS(x)              (g_stTxLTInfo.ucAdjustReqLane01 = ((g_stTxLTInfo.ucAdjustReqLane01 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

#define GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()               ((g_stTxLTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define SET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS(x)              (g_stTxLTInfo.ucAdjustReqLane23 = ((g_stTxLTInfo.ucAdjustReqLane23 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()               ((g_stTxLTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)
#define SET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS(x)              (g_stTxLTInfo.ucAdjustReqLane23 = ((g_stTxLTInfo.ucAdjustReqLane23 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

//--------------------------------------------------
// Macros of DP Tx HDCP Infomation
//--------------------------------------------------
#define GET_DP_TX_HDCP_DOWNSTREAM_EVENT()                   (g_stTxHDCPAuthInfo.ucAuthDownstreamEvent)
#define SET_DP_TX_HDCP_DOWNSTREAM_EVENT(x)                  (g_stTxHDCPAuthInfo.ucAuthDownstreamEvent = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_EVENT()                   (g_stTxHDCPAuthInfo.ucAuthDownstreamEvent = _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE)

#define GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stTxHDCPAuthInfo.b1IsHDCPSupported)
#define SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stTxHDCPAuthInfo.b1IsHDCPSupported = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED()               (g_stTxHDCPAuthInfo.b1IsHDCPSupported = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stTxHDCPAuthInfo.b1IsDownstreamRepeater)
#define SET_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stTxHDCPAuthInfo.b1IsDownstreamRepeater = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER()                (g_stTxHDCPAuthInfo.b1IsDownstreamRepeater = _FALSE)

#define GET_DP_TX_HDCP_AUTH_STATE()                         (g_stTxHDCPAuthInfo.b4AuthState)
#define SET_DP_TX_HDCP_AUTH_STATE(x)                        (g_stTxHDCPAuthInfo.b4AuthState = (x))

#define GET_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stTxHDCPAuthInfo.b1AuthStateChange)
#define SET_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stTxHDCPAuthInfo.b1AuthStateChange = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_STATE_CHANGE()                  (g_stTxHDCPAuthInfo.b1AuthStateChange = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT()            (g_stTxHDCPAuthInfo.ucBInfoDevice & 0x7F)
#define GET_DP_TX_HDCP_DOWNSTREAM_DEPTH()                   (g_stTxHDCPAuthInfo.ucBInfoDepth & 0x03)

#define GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE()            (g_stTxHDCPAuthInfo.ucBInfoDevice)
#define SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE(x)           (g_stTxHDCPAuthInfo.ucBInfoDevice = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE()            (g_stTxHDCPAuthInfo.ucBInfoDevice = 0x00)

#define GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH()             (g_stTxHDCPAuthInfo.ucBInfoDepth)
#define SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH(x)            (g_stTxHDCPAuthInfo.ucBInfoDepth = (x))
#define CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH()             (g_stTxHDCPAuthInfo.ucBInfoDepth = 0x00)

#define GET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stTxHDCPAuthInfo.b1R0Timeout)
#define SET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stTxHDCPAuthInfo.b1R0Timeout = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT()              (g_stTxHDCPAuthInfo.b1R0Timeout = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stTxHDCPAuthInfo.b1VReadyTimeout)
#define SET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stTxHDCPAuthInfo.b1VReadyTimeout = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT()         (g_stTxHDCPAuthInfo.b1VReadyTimeout = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stTxHDCPAuthInfo.b1PollingVReady)
#define SET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stTxHDCPAuthInfo.b1PollingVReady = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY()         (g_stTxHDCPAuthInfo.b1PollingVReady = _FALSE)

#define GET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stTxHDCPAuthInfo.b1VReadyBit)
#define SET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stTxHDCPAuthInfo.b1VReadyBit = _TRUE)
#define CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT()             (g_stTxHDCPAuthInfo.b1VReadyBit = _FALSE)

#define GET_DP_TX_HDCP_AUTH_START()                         (g_stTxHDCPAuthInfo.b1AuthStart)
#define SET_DP_TX_HDCP_AUTH_START()                         (g_stTxHDCPAuthInfo.b1AuthStart = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_START()                         (g_stTxHDCPAuthInfo.b1AuthStart = _FALSE)

#define GET_DP_TX_HDCP_AUTH_HOLD()                          (g_stTxHDCPAuthInfo.b1AuthHold)
#define SET_DP_TX_HDCP_AUTH_HOLD()                          (g_stTxHDCPAuthInfo.b1AuthHold = _TRUE)
#define CLR_DP_TX_HDCP_AUTH_HOLD()                          (g_stTxHDCPAuthInfo.b1AuthHold = _FALSE)

#define GET_DP_TX_HDCP_ENCRYPT_STATUS()                     (ScalerGetBit(PBB_30_DPTX_HDCP_CTRL1, _BIT1) == _BIT1)

//--------------------------------------------------
// Macros of DP Tx CTS Test
//--------------------------------------------------
#define GET_DP_TX_CTS_TEST_REQUEST_TYPE(x)                  (g_ucDpTxCtsRequestType & (x))
#define SET_DP_TX_CTS_TEST_REQUEST_TYPE(x)                  (g_ucDpTxCtsRequestType = (x))
#define CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(x)           (g_ucDpTxCtsRequestType &= ~(x))
#define CLR_DP_TX_CTS_TEST_REQUEST_TYPE()                   (g_ucDpTxCtsRequestType = _DP_TX_CTS_NONE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3ModeState : 3;
    BYTE b1ModeStateChanged : 1;
    BYTE b2HPDEvent : 2;
    BYTE b1FirstHPD : 1;
    BYTE b1IRQHPDDetected : 1;
//------------------------------------
    BYTE b1ForceLT : 1;
    BYTE b1ExceedBandwidth : 1;
} StructDPTxModeInfoType;

typedef struct
{
    BYTE b3ColorDepth : 3;
    BYTE b3ColorSpace : 3;
    BYTE b1AudioReadyToPlay : 1;
    BYTE b1InterlaceMode : 1;
//------------------------------------
    BYTE b3AudioChannelCount : 3;
    BYTE b1InterlaceVTotalNumber : 1;
    BYTE ucCurrnetAudioFrequency;
    WORD usInputPixelClk;
    WORD usHorizontalDataEnablePeriod;
} StructDPTxInputInfo;

typedef struct
{
    BYTE b4AuthState : 4;
    BYTE b1AuthStateChange : 1;
    BYTE b1IsHDCPSupported : 1;
    BYTE b1IsDownstreamRepeater : 1;
    BYTE b1R0Timeout : 1;
//------------------------------------
    BYTE b1VReadyTimeout : 1;
    BYTE b1PollingVReady : 1;
    BYTE b1VReadyBit : 1;
    BYTE b1AuthStart : 1;
    BYTE b1AuthHold : 1;
    BYTE ucAuthDownstreamEvent;
    BYTE ucBInfoDevice;
    BYTE ucBInfoDepth;
} StructDPTxHDCPAuthInfo;

typedef enum
{
    _DP_TX_LEVEL_0 = 0x00,
    _DP_TX_LEVEL_1,
    _DP_TX_LEVEL_2,
    _DP_TX_LEVEL_3,
} EnumDpTxSignalLevel;

typedef enum
{
    _DP_TP_NONE = 0x00,
    _DP_TP_1,
    _DP_TP_2,
    _DP_TP_3,
} EnumDpTxTrainPattern;

typedef enum
{
    _DP_LANE0_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DP_LANE1_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DP_LANE2_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DP_LANE3_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DP_SCRAMBLING_DISABLE = _BIT5,
} EnumDpTxLinkTrainAdditionalInfo;

// Main Link Pattern
typedef enum
{
    _DP_TX_OUTPUT_IDLE_PATTERN = 0x00,
    _DP_TX_OUTPUT_TPS1,
    _DP_TX_OUTPUT_TPS2,
    _DP_TX_OUTPUT_TPS3,
    _DP_TX_OUTPUT_VIDEO_PATTERN,
    _DP_TX_OUTPUT_PRBS7,
    _DP_TX_OUTPUT_80BIT_CUSTOM_PATTERN,
    _DP_TX_OUTPUT_EYE_PATTERN,
} EnumDPTxMainLinkPattern;

//--------------------------------------------------
// Enumerations of DP Tx Mode State
//--------------------------------------------------
typedef enum
{
    _DP_TX_MODE_STATUS_INITIAL = 0x00,
    _DP_TX_MODE_STATUS_LINK_TRAINING,
    _DP_TX_MODE_STATUS_LINK_ON,
    _DP_TX_MODE_STATUS_UNPLUG,
    _DP_TX_MODE_STATUS_DC_OFF,
} EnumDPTxModeStatus;

typedef enum
{
    _DP_TX_HPD_NO_EVENT = 0x00,
    _DP_TX_HPD_UNPLUG_EVENT,
    _DP_TX_HPD_PLUG_EVENT,
    _DP_TX_HPD_IRQ_EVENT,
} EnumDPTxHPDEvent;

typedef enum
{
    _DP_TX_IRQ_HPD_NONE = 0x00,
    _DP_TX_IRQ_HPD_CP_IRQ = _BIT0,
    _DP_TX_IRQ_HPD_MCCS_IRQ = _BIT1,
    _DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ = _BIT2,
    _DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ = _BIT3,
    _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ = _BIT4,
    _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ = _BIT5,
    _DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ = _BIT6,
    _DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST = _BIT7,
} EnumDPTxIRQEventType;

//--------------------------------------------------
//HDCP IRQ Type
//--------------------------------------------------
typedef enum
{
    _DP_TX_IRQ_HDCP_NONE = 0,
    _DP_TX_IRQ_HDCP_V_READY = _BIT0,
    _DP_TX_IRQ_HDCP_R0_AVAILABLE = _BIT1,
    _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL = _BIT2,
    _DP_TX_IRQ_HDCP_REAUTH_REQUEST = _BIT3,
} EnumDPTxTRQEventHDCPType;

typedef enum
{
    _DP_TX_SOURCE_NONE = 0x00,
    _DP_TX_SOURCE_MST2SST,
    _DP_TX_SOURCE_MST,
    _DP_TX_SOURCE_CLONE,
} EnumDPTxInputSource;


typedef enum
{
    _DP_TX_TRAINING_PATTERN1 = 0x00,
    _DP_TX_TRAINING_PATTERN2,
    _DP_TX_TRAINING_PATTERN_END ,
} EnumDPTxLTStatus;

typedef enum
{
    _DP_TX_TRAINING_NO_RESULT = 0x00,
    _DP_TX_TRAINING_PATTERN1_FAIL,
    _DP_TX_TRAINING_PATTERN2_FAIL,
    _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL,
    _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL,
    _DP_TX_TRAINING_PATTERN1_PASS,
    _DP_TX_TRAINING_PATTERN2_PASS,
    _DP_TX_TRAINING_PASS,
    _DP_TX_TRAINING_FAIL,
} EnumDPTxLTResult;

//--------------------------------------------------
//HDCP RX Authentication Downstream Event
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_NONE = 0,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_LINK_INTEGRITY_FAIL,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_MSG_QUERY_REAUTH,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PLUG_CHANGED,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS,
    _DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX,
} EnumDPTxHDCPDownstreamAuthStatus;

//--------------------------------------------------
//HDCP Auth State
//--------------------------------------------------
typedef enum
{
    _DP_TX_HDCP_STATE_IDLE = 0,
    _DP_TX_HDCP_STATE_AUTH_1,
    _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0,
    _DP_TX_HDCP_STATE_AUTH_2,
    _DP_TX_HDCP_STATE_AUTH_PASS,
} EnumDPTxHDCPAuthState;

//--------------------------------------------------
//Audio Packet Type
//--------------------------------------------------
typedef enum
{
    _SEC_PACKET_TYPE_AUDIO_TIMESTAMP = 0x01,
    _SEC_PACKET_TYPE_AUDIO_STREAM = 0x02,
    _SEC_PACKET_TYPE_VSC = 0x07,
    _SEC_PACKET_TYPE_INFOFRAME_AVI = 0x0A,
    _SEC_PACKET_TYPE_INFOFRAME_AUDIO = 0x0C,
    _SEC_PACKET_TYPE_INFOFRAME_MPEG = 0x0D,
    _SEC_PACKET_TYPE_INFOFRAME_RSV = 0x0F,
} EnumDPTxSecDataPacketType;

//--------------------------------------------------
// Enumerations of Audio Play State
//--------------------------------------------------
typedef enum
{
    _DP_TX_AUDIO_OFF = 0x00,
    _DP_TX_AUDIO_ON,
    _DP_TX_AUDIO_STANDBY,
    _DP_TX_AUDIO_PRESET,
} EnumDPTxAudioPlayState;

//--------------------------------------------------
// Enumerations of DP TX CTS Test
//--------------------------------------------------
typedef enum
{
    _DP_TX_CTS_NONE = 0x00,
    _DP_TX_CTS_TEST_LINK_TRAINING = _BIT0,
    _DP_TX_CTS_TEST_PATTERN = _BIT1,
    _DP_TX_CTS_TEST_EDID_READ = _BIT2,
    _DP_TX_CTS_PHY_TEST_PATTERN = _BIT3,
    _DP_TX_CTS_FAUX_TEST_PATTERN = _BIT4,
} EnumDPTxCtsTestRequestType;

typedef enum
{
    _TEST_ACK = _BIT0,
    _TEST_NAK = _BIT1,
    _TEST_EDID_CHECKSUM_WRITE = _BIT2,
} EnumDPTxCtsTestResponseType;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

extern StructDPTxModeInfoType g_stTxModeInfo;
extern StructDPTxInputInfo g_stTxInputInfo;
extern StructDPTxHDCPAuthInfo g_stTxHDCPAuthInfo;
extern EnumDPTxIRQEventType g_enumDpTxIRQType;
extern EnumDPTxIRQEventType g_enumDpTxIRQTypeInt;
extern EnumDPTxTRQEventHDCPType g_enumDpTxIRQHDCPType;
extern StructTimingInfo g_stDPTxInputTimingInfo;

extern bit g_bDpTxIRQHPDDetected;

extern bit g_bDpTxSourceChanged;
extern BYTE g_ucDpTxStreamSource;

extern BYTE g_pucDpTxHdcpKsvFifo[_DP_TX_HDCP_DEVICE_COUNT_MAX * 5];
extern BYTE g_pucDpTxHdcpDownStreamV[20];

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
extern bit g_bDpTxVscSdpColorMode;
#endif
//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

extern void ScalerDpTxInitial(void);
extern void ScalerDpTxStateChangeEvent(EnumDPTxModeStatus enumModeState);
extern void ScalerDpTxSetStreamSource(EnumDPTxInputSource enumStreamSource);
extern void ScalerDpTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource);
extern void ScalerDpTxAudioSetting(void);
extern WORD ScalerDpTxAudioGetSamplingFreqPacket(void);
extern void ScalerDpTxSetSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
extern void ScalerDpTxClearSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
extern bit ScalerDpTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
extern bit ScalerDpTxMeasureInputInfo(void);
extern BYTE ScalerDpTxCloneGetCurrentInputPort(void);
extern void ScalerDpTxHDCPAuth2ShaRun(bit bIsFirst);
extern void ScalerDpTxHDCPChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState);
extern void ScalerDpTxHDCPTimeoutToReadR0Event(void);
extern void ScalerDpTxHDCPTimeoutForVReadyEvent(void);
extern void ScalerDpTxHDCPPollingVReadyEvent(void);
extern void ScalerDpTxHDCPEncryptSignalProc(bit bEnable);

#endif // End of #if(_DP_TX_SUPPORT == _ON)


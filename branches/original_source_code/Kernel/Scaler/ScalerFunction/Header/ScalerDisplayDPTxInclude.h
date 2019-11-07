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
// ID Code      : ScalerDisplayDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_DPTX)

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_DPTX_SPREAD_SPEED == _SPEED_33K)
#define _DISPLAY_DP_TX_SSC_FREQ                                     32
#elif(_PANEL_DPTX_SPREAD_SPEED == _SPEED_30K)
#define _DISPLAY_DP_TX_SSC_FREQ                                     31
#else
#define _DISPLAY_DP_TX_SSC_FREQ                                     32
#endif

#define _DISPLAY_DP_TX_AUX_DIFF_MODE                                0
#define _DISPLAY_DP_TX_AUX_SINGLE_MODE                              1

#define GET_DISPLAY_DP_TX_SSCG_CONFIG()                             (g_bDptxSscEn)
#define SET_DISPLAY_DP_TX_SSCG_CONFIG(x)                            (g_bDptxSscEn = (x))

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define GET_DISPLAY_DP_TX1_HPD_DEBOUNCE_LEVEL()                     (ScalerGetBit(P9C_70_HPD_CTRL, _BIT2) >> 2)
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define GET_DISPLAY_DP_TX2_HPD_DEBOUNCE_LEVEL()                     (ScalerGetBit(P9E_70_HPD_CTRL, _BIT2) >> 2)
#endif

//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define GET_DISPLAY_DP_TX1_DPCD_REV()                               (g_stDisplayDPTx1Info.ucDPCDRev)
#define SET_DISPLAY_DP_TX1_DPCD_REV(x)                              (g_stDisplayDPTx1Info.ucDPCDRev = (x))

#define GET_DISPLAY_DP_TX1_LINK_RATE()                              (g_stDisplayDPTx1Info.ucLinkRate)
#define SET_DISPLAY_DP_TX1_LINK_RATE(x)                             (g_stDisplayDPTx1Info.ucLinkRate = (x))

#define GET_DISPLAY_DP_TX1_LANE_NUM()                               (g_stDisplayDPTx1Info.b3LaneNum)
#define SET_DISPLAY_DP_TX1_LANE_NUM(x)                              (g_stDisplayDPTx1Info.b3LaneNum = (x))

#define GET_DISPLAY_DP_TX1_MAX_LINK_RATE()                          (g_stDisplayDPTx1Info.ucMaxLinkRate)
#define SET_DISPLAY_DP_TX1_MAX_LINK_RATE(x)                         (g_stDisplayDPTx1Info.ucMaxLinkRate = (x))

#define GET_DISPLAY_DP_TX1_ENHANCE_FRAMING()                        (g_stDisplayDPTx1Info.b1EnhanceFraming)
#define SET_DISPLAY_DP_TX1_ENHANCE_FRAMING(x)                       (g_stDisplayDPTx1Info.b1EnhanceFraming = (x))

#define GET_DISPLAY_DP_TX1_ALTERNATE_SR_CAPABLE()                   (g_stDisplayDPTx1Info.b1AlternateSrCapable)
#define SET_DISPLAY_DP_TX1_ALTERNATE_SR_CAPABLE(x)                  (g_stDisplayDPTx1Info.b1AlternateSrCapable = (x))

#define GET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE()                 (g_stDisplayDPTx1Info.b1FramingChangeCapable)
#define SET_DISPLAY_DP_TX1_FRAMING_CHANGE_CAPABLE(x)                (g_stDisplayDPTx1Info.b1FramingChangeCapable = (x))

#define GET_DISPLAY_DP_TX1_DOWN_SPREAD()                            (g_stDisplayDPTx1Info.b1SSCSupport)
#define SET_DISPLAY_DP_TX1_DOWN_SPREAD(x)                           (g_stDisplayDPTx1Info.b1SSCSupport = (x))

#define GET_DISPLAY_DP_TX1_TP3_SUPPORT()                            (g_stDisplayDPTx1Info.b1TP3Support)
#define SET_DISPLAY_DP_TX1_TP3_SUPPORT()                            (g_stDisplayDPTx1Info.b1TP3Support = _TRUE)
#define CLR_DISPLAY_DP_TX1_TP3_SUPPORT()                            (g_stDisplayDPTx1Info.b1TP3Support = _FALSE)
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define GET_DISPLAY_DP_TX2_DPCD_REV()                               (g_stDisplayDPTx2Info.ucDPCDRev)
#define SET_DISPLAY_DP_TX2_DPCD_REV(x)                              (g_stDisplayDPTx2Info.ucDPCDRev = (x))

#define GET_DISPLAY_DP_TX2_LINK_RATE()                              (g_stDisplayDPTx2Info.ucLinkRate)
#define SET_DISPLAY_DP_TX2_LINK_RATE(x)                             (g_stDisplayDPTx2Info.ucLinkRate = (x))

#define GET_DISPLAY_DP_TX2_LANE_NUM()                               (g_stDisplayDPTx2Info.b3LaneNum)
#define SET_DISPLAY_DP_TX2_LANE_NUM(x)                              (g_stDisplayDPTx2Info.b3LaneNum = (x))

#define GET_DISPLAY_DP_TX2_MAX_LINK_RATE()                          (g_stDisplayDPTx2Info.ucMaxLinkRate)
#define SET_DISPLAY_DP_TX2_MAX_LINK_RATE(x)                         (g_stDisplayDPTx2Info.ucMaxLinkRate = (x))

#define GET_DISPLAY_DP_TX2_ENHANCE_FRAMING()                        (g_stDisplayDPTx2Info.b1EnhanceFraming)
#define SET_DISPLAY_DP_TX2_ENHANCE_FRAMING(x)                       (g_stDisplayDPTx2Info.b1EnhanceFraming = (x))

#define GET_DISPLAY_DP_TX2_ALTERNATE_SR_CAPABLE()                   (g_stDisplayDPTx2Info.b1AlternateSrCapable)
#define SET_DISPLAY_DP_TX2_ALTERNATE_SR_CAPABLE(x)                  (g_stDisplayDPTx2Info.b1AlternateSrCapable = (x))

#define GET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE()                 (g_stDisplayDPTx2Info.b1FramingChangeCapable)
#define SET_DISPLAY_DP_TX2_FRAMING_CHANGE_CAPABLE(x)                (g_stDisplayDPTx2Info.b1FramingChangeCapable = (x))

#define GET_DISPLAY_DP_TX2_DOWN_SPREAD()                            (g_stDisplayDPTx2Info.b1SSCSupport)
#define SET_DISPLAY_DP_TX2_DOWN_SPREAD(x)                           (g_stDisplayDPTx2Info.b1SSCSupport = (x))

#define GET_DISPLAY_DP_TX2_TP3_SUPPORT()                            (g_stDisplayDPTx2Info.b1TP3Support)
#define SET_DISPLAY_DP_TX2_TP3_SUPPORT()                            (g_stDisplayDPTx2Info.b1TP3Support = _TRUE)
#define CLR_DISPLAY_DP_TX2_TP3_SUPPORT()                            (g_stDisplayDPTx2Info.b1TP3Support = _FALSE)
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

//--------------------------------------------------
// Macros of DP Tx Input Infomation
//--------------------------------------------------
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define GET_DISPLAY_DP_TX1_INPUT_COLOR_DEPTH()                      (g_stDisplayDPTx1InputInfo.b3ColorDepth)
#define SET_DISPLAY_DP_TX1_INPUT_COLOR_DEPTH(x)                     (g_stDisplayDPTx1InputInfo.b3ColorDepth = (x))

#define GET_DISPLAY_DP_TX1_INPUT_COLOR_SPACE()                      (g_stDisplayDPTx1InputInfo.b3ColorSpace)
#define SET_DISPLAY_DP_TX1_INPUT_COLOR_SPACE(x)                     (g_stDisplayDPTx1InputInfo.b3ColorSpace = (x))

#define GET_DISPLAY_DP_TX1_LINK_CONFIG()                            (g_stDisplayDPTx1InputInfo.b1LinkConfig)
#define SET_DISPLAY_DP_TX1_LINK_CONFIG(x)                           (g_stDisplayDPTx1InputInfo.b1LinkConfig = (x))
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define GET_DISPLAY_DP_TX2_INPUT_COLOR_DEPTH()                      (g_stDisplayDPTx2InputInfo.b3ColorDepth)
#define SET_DISPLAY_DP_TX2_INPUT_COLOR_DEPTH(x)                     (g_stDisplayDPTx2InputInfo.b3ColorDepth = (x))

#define GET_DISPLAY_DP_TX2_INPUT_COLOR_SPACE()                      (g_stDisplayDPTx2InputInfo.b3ColorSpace)
#define SET_DISPLAY_DP_TX2_INPUT_COLOR_SPACE(x)                     (g_stDisplayDPTx2InputInfo.b3ColorSpace = (x))

#define GET_DISPLAY_DP_TX2_LINK_CONFIG()                            (g_stDisplayDPTx2InputInfo.b1LinkConfig)
#define SET_DISPLAY_DP_TX2_LINK_CONFIG(x)                           (g_stDisplayDPTx2InputInfo.b1LinkConfig = (x))
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

//--------------------------------------------------
// Macros of DP Tx Link Infomation
//--------------------------------------------------

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define GET_DISPLAY_DP_TX1_LT_STATE()                               (g_stDisplayDPTx1LTInfo.b2LinkTrainingState)
#define SET_DISPLAY_DP_TX1_LT_STATE(x)                              (g_stDisplayDPTx1LTInfo.b2LinkTrainingState = (x))

#define GET_DISPLAY_DP_TX1_LT_RESULT()                              (g_stDisplayDPTx1LTInfo.b4LinkTrainingResult)
#define SET_DISPLAY_DP_TX1_LT_RESULT(x)                             (g_stDisplayDPTx1LTInfo.b4LinkTrainingResult = (x))

#define GET_DISPLAY_DP_TX1_LINK_PBN_PER_TIMESOLT()                  (g_stDisplayDPTx1LTInfo.ucLinkPBNPerTimeSlot)
#define SET_DISPLAY_DP_TX1_LINK_PBN_PER_TIMESOLT(x)                 (g_stDisplayDPTx1LTInfo.ucLinkPBNPerTimeSlot = (x))

#define GET_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane0SameVolCnt)
#define ADD_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane0SameVolCnt++)
#define CLR_DISPLAY_DP_TX1_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane0SameVolCnt = 0)

#define GET_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane1SameVolCnt)
#define ADD_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane1SameVolCnt++)
#define CLR_DISPLAY_DP_TX1_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane1SameVolCnt = 0)

#define GET_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane2SameVolCnt)
#define ADD_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane2SameVolCnt++)
#define CLR_DISPLAY_DP_TX1_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane2SameVolCnt = 0)

#define GET_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane3SameVolCnt)
#define ADD_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane3SameVolCnt++)
#define CLR_DISPLAY_DP_TX1_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx1LTInfo.b3TP1Lane3SameVolCnt = 0)

#define GET_DISPLAY_DP_TX1_TP2_CNT()                                (g_stDisplayDPTx1LTInfo.b3TP2count)
#define ADD_DISPLAY_DP_TX1_TP2_CNT()                                (g_stDisplayDPTx1LTInfo.b3TP2count++)
#define CLR_DISPLAY_DP_TX1_TP2_CNT()                                (g_stDisplayDPTx1LTInfo.b3TP2count = 0)

#define GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING()                (g_stDisplayDPTx1LTInfo.ucLane0Adjust & 0x03)
#define SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx1LTInfo.ucLane0Adjust = ((g_stDisplayDPTx1LTInfo.ucLane0Adjust & 0xFC) | (x)))

#define GET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH()      (bit)((g_stDisplayDPTx1LTInfo.ucLane0Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX1_LANE0_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING()                (g_stDisplayDPTx1LTInfo.ucLane1Adjust & 0x03)
#define SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx1LTInfo.ucLane1Adjust = ((g_stDisplayDPTx1LTInfo.ucLane1Adjust & 0xFC) | (x)))

#define GET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH()      (bit)((g_stDisplayDPTx1LTInfo.ucLane1Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX1_LANE1_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING()                (g_stDisplayDPTx1LTInfo.ucLane2Adjust & 0x03)
#define SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx1LTInfo.ucLane2Adjust = ((g_stDisplayDPTx1LTInfo.ucLane2Adjust & 0xFC) | (x)))

#define GET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH()      (bit)((g_stDisplayDPTx1LTInfo.ucLane2Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX1_LANE2_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING()                (g_stDisplayDPTx1LTInfo.ucLane3Adjust & 0x03)
#define SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx1LTInfo.ucLane3Adjust = ((g_stDisplayDPTx1LTInfo.ucLane3Adjust & 0xFC) | (x)))

#define GET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH()      (bit)((g_stDisplayDPTx1LTInfo.ucLane3Adjust & _BIT2) >> 2)
#define SET_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX1_LANE3_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx1LTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx1LTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx1LTInfo.ucLane0Adjust = ((g_stDisplayDPTx1LTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX1_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx1LTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx1LTInfo.ucLane1Adjust = ((g_stDisplayDPTx1LTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX1_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx1LTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx1LTInfo.ucLane2Adjust = ((g_stDisplayDPTx1LTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX1_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx1LTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx1LTInfo.ucLane3Adjust = ((g_stDisplayDPTx1LTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX1_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx1LTInfo.ucLane3Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX1_LANE0_CR_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX1_LANE1_CR_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DISPLAY_DP_TX1_LANE2_CR_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX1_LANE3_CR_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DISPLAY_DP_TX1_LANE0_EQ_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX1_LANE1_EQ_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_DISPLAY_DP_TX1_LANE2_EQ_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX1_LANE3_EQ_DONE()                          ((g_stDisplayDPTx1LTInfo.ucLane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_DISPLAY_DP_TX1_LANE_ALIGN_DONE()                        ((g_stDisplayDPTx1LTInfo.ucLaneAlignStatus & _BIT0) == _BIT0)


#define GET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING()                 (g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX1_LANE0_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING()                 ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX1_LANE1_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING()                 (g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX1_LANE2_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING()                 ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX1_LANE3_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX1_LANE0_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TX1_LANE1_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define GET_DISPLAY_DP_TX1_LANE2_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TX1_LANE3_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx1LTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define GET_DISPLAY_DP_TX2_LT_STATE()                               (g_stDisplayDPTx2LTInfo.b2LinkTrainingState)
#define SET_DISPLAY_DP_TX2_LT_STATE(x)                              (g_stDisplayDPTx2LTInfo.b2LinkTrainingState = (x))

#define GET_DISPLAY_DP_TX2_LT_RESULT()                              (g_stDisplayDPTx2LTInfo.b4LinkTrainingResult)
#define SET_DISPLAY_DP_TX2_LT_RESULT(x)                             (g_stDisplayDPTx2LTInfo.b4LinkTrainingResult = (x))

#define GET_DISPLAY_DP_TX2_LINK_PBN_PER_TIMESOLT()                  (g_stDisplayDPTx2LTInfo.ucLinkPBNPerTimeSlot)
#define SET_DISPLAY_DP_TX2_LINK_PBN_PER_TIMESOLT(x)                 (g_stDisplayDPTx2LTInfo.ucLinkPBNPerTimeSlot = (x))

#define GET_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane0SameVolCnt)
#define ADD_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane0SameVolCnt++)
#define CLR_DISPLAY_DP_TX2_TP1_LANE0_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane0SameVolCnt = 0)

#define GET_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane1SameVolCnt)
#define ADD_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane1SameVolCnt++)
#define CLR_DISPLAY_DP_TX2_TP1_LANE1_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane1SameVolCnt = 0)

#define GET_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane2SameVolCnt)
#define ADD_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane2SameVolCnt++)
#define CLR_DISPLAY_DP_TX2_TP1_LANE2_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane2SameVolCnt = 0)

#define GET_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane3SameVolCnt)
#define ADD_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane3SameVolCnt++)
#define CLR_DISPLAY_DP_TX2_TP1_LANE3_SAME_VOL_CNT()                 (g_stDisplayDPTx2LTInfo.b3TP1Lane3SameVolCnt = 0)

#define GET_DISPLAY_DP_TX2_TP2_CNT()                                (g_stDisplayDPTx2LTInfo.b3TP2count)
#define ADD_DISPLAY_DP_TX2_TP2_CNT()                                (g_stDisplayDPTx2LTInfo.b3TP2count++)
#define CLR_DISPLAY_DP_TX2_TP2_CNT()                                (g_stDisplayDPTx2LTInfo.b3TP2count = 0)

#define GET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING()                (g_stDisplayDPTx2LTInfo.ucLane0Adjust & 0x03)
#define SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx2LTInfo.ucLane0Adjust = ((g_stDisplayDPTx2LTInfo.ucLane0Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX2_LANE0_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING()                (g_stDisplayDPTx2LTInfo.ucLane1Adjust & 0x03)
#define SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx2LTInfo.ucLane1Adjust = ((g_stDisplayDPTx2LTInfo.ucLane1Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX2_LANE1_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING()                (g_stDisplayDPTx2LTInfo.ucLane2Adjust & 0x03)
#define SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx2LTInfo.ucLane2Adjust = ((g_stDisplayDPTx2LTInfo.ucLane2Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX2_LANE2_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING()                (g_stDisplayDPTx2LTInfo.ucLane3Adjust & 0x03)
#define SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING(x)               (g_stDisplayDPTx2LTInfo.ucLane3Adjust = ((g_stDisplayDPTx2LTInfo.ucLane3Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX2_LANE3_CURRENT_VOL_SWING_MAX_REACH()      (g_stDisplayDPTx2LTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx2LTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx2LTInfo.ucLane0Adjust = ((g_stDisplayDPTx2LTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX2_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx2LTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx2LTInfo.ucLane1Adjust = ((g_stDisplayDPTx2LTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX2_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx2LTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx2LTInfo.ucLane2Adjust = ((g_stDisplayDPTx2LTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX2_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS()             ((g_stDisplayDPTx2LTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS(x)            (g_stDisplayDPTx2LTInfo.ucLane3Adjust = ((g_stDisplayDPTx2LTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX2_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()   (g_stDisplayDPTx2LTInfo.ucLane3Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX2_LANE0_CR_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX2_LANE1_CR_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DISPLAY_DP_TX2_LANE2_CR_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX2_LANE3_CR_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DISPLAY_DP_TX2_LANE0_EQ_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX2_LANE1_EQ_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_DISPLAY_DP_TX2_LANE2_EQ_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX2_LANE3_EQ_DONE()                          ((g_stDisplayDPTx2LTInfo.ucLane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_DISPLAY_DP_TX2_LANE_ALIGN_DONE()                        ((g_stDisplayDPTx2LTInfo.ucLaneAlignStatus & _BIT0) == _BIT0)

#define GET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING()                 (g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX2_LANE0_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING()                 ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX2_LANE1_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING()                 (g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX2_LANE2_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING()                 ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX2_LANE3_ADJUST_VOL_SWING(x)                (g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX2_LANE0_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TX2_LANE1_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define GET_DISPLAY_DP_TX2_LANE2_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define GET_DISPLAY_DP_TX2_LANE3_ADJUST_PRE_EMPHASIS()              ((g_stDisplayDPTx2LTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b3ColorDepth : 3;
    BYTE b3ColorSpace : 3;
    WORD usInputPixelClk;
    BYTE b1LinkConfig : 1;
} StructDisplayDPTxInputInfo;

typedef enum
{
    _DISPLAY_DP_TX_LANE_0 = 0x00,
    _DISPLAY_DP_TX_LANE_1,
    _DISPLAY_DP_TX_LANE_2,
    _DISPLAY_DP_TX_LANE_3,
} EnumDisplayDPTxLane;

typedef enum
{
    _DISPLAY_DP_TX_TP_NONE = 0x00,
    _DISPLAY_DP_TX_TP_1,
    _DISPLAY_DP_TX_TP_2,
    _DISPLAY_DP_TX_TP_3,
} EnumDisplayDPTxTrainPattern;

typedef enum
{
    _DISPLAY_DP_TX_LANE0_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DISPLAY_DP_TX_LANE1_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DISPLAY_DP_TX_LANE2_MAX_POST_CURSOR2_REACHED = _BIT2,
    _DISPLAY_DP_TX_LANE3_MAX_POST_CURSOR2_REACHED = _BIT6,
    _DISPLAY_DP_TX_SCRAMBLING_DISABLE = _BIT5,
} EnumDisplayDPTxLinkTrainAdditionalInfo;

// Main Link Pattern
typedef enum
{
    _DISPLAY_DP_TX_OUTPUT_IDLE_PATTERN = 0x00,
    _DISPLAY_DP_TX_OUTPUT_TPS1,
    _DISPLAY_DP_TX_OUTPUT_TPS2,
    _DISPLAY_DP_TX_OUTPUT_TPS3,
    _DISPLAY_DP_TX_OUTPUT_VIDEO_PATTERN,
    _DISPLAY_DP_TX_OUTPUT_PRBS7,
} EnumDisplayDPTxMainLinkPattern;

//--------------------------------------------------
// Enumerations of DP Tx Mode State
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_TRAINING_PATTERN1 = 0x00,
    _DISPLAY_DP_TX_TRAINING_PATTERN2,
    _DISPLAY_DP_TX_TRAINING_PATTERN_END,
} EnumDisplayDPTxLTStatus;

typedef enum
{
    _DISPLAY_DP_TX_TRAINING_NO_RESULT = 0x00,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL,
    _DISPLAY_DP_TX_TRAINING_PATTERN1_PASS,
    _DISPLAY_DP_TX_TRAINING_PATTERN2_PASS,
    _DISPLAY_DP_TX_TRAINING_PASS,
    _DISPLAY_DP_TX_TRAINING_FAIL,
} EnumDisplayDPTxLTResult;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bDptxSscEn;

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern StructDownStreamInfo g_stDisplayDPTx1Info;
extern StructDPTxLTInfo g_stDisplayDPTx1LTInfo;
extern StructDisplayDPTxInputInfo g_stDisplayDPTx1InputInfo;
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
extern StructDownStreamInfo g_stDisplayDPTx2Info;
extern StructDPTxLTInfo g_stDisplayDPTx2LTInfo;
extern StructDisplayDPTxInputInfo g_stDisplayDPTx2InputInfo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern void ScalerDisplayDPTx1Initial(void);
extern bit ScalerDisplayDPTx1LinkConfig(void);
extern void ScalerDisplayDPTx1VideoStreamOutput(bit bOutput);
extern void ScalerDisplayDPTx1LinkTraining(void);
extern void ScalerDisplayDPTx1LinkForceOutput(void);
extern void ScalerDisplayDPTx1SignalReset(void);
extern void ScalerDisplayDPTx1MLPHYSet(void);
extern bit ScalerDisplayDPTx1NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx1NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
#endif

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
extern void ScalerDisplayDPTx2Initial(void);
extern bit ScalerDisplayDPTx2LinkConfig(void);
extern void ScalerDisplayDPTx2VideoStreamOutput(bit bOutput);
extern void ScalerDisplayDPTx2LinkTraining(void);
extern void ScalerDisplayDPTx2TPInitialSet(void);
extern void ScalerDisplayDPTx2LinkForceOutput(void);
extern void ScalerDisplayDPTx2SignalReset(void);
extern void ScalerDisplayDPTx2MLPHYSet(void);
extern bit ScalerDisplayDPTx2NativeAuxWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx2NativeAuxRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
#endif
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

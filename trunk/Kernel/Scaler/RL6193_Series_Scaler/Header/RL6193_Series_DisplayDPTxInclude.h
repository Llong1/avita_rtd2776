/********************************************************************************/
/*   The  Software  is  proprietary,  confidential,  and  valuable to Realtek   */
/*   Semiconductor  Corporation  ("Realtek").  All  rights, including but not   */
/*   limited  to  copyrights,  patents,  trademarks, trade secrets, mask work   */
/*   rights, and other similar rights and interests, are reserved to Realtek.   */
/*   Without  prior  written  consent  from  Realtek,  copying, reproduction,   */
/*   modification,  distribution,  or  otherwise  is strictly prohibited. The   */
/*   Software  shall  be  kept  strictly  in  confidence,  and  shall  not be   */
/*   disclosed to or otherwise accessed by any third party.                     */
/*   c<2003> - <2012>                                                           */
/*   The Software is provided "AS IS" without any warranty of any kind,         */
/*   express, implied, statutory or otherwise.                                  */
/********************************************************************************/

//----------------------------------------------------------------------------------------------------
// ID Code      : RL6193_Series_DisplayDPTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_DPTX)
//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************
#if(_DISPLAY_DP_TX_PORT_1 == _ON)
#define SET_DISPLAY_DP_TX1_MVID_FW_MODE()                           ;
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
#define SET_DISPLAY_DP_TX2_MVID_FW_MODE()                           ;
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
//--------------------------------------------------
// Macros of DP Tx Downstream Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TX_DPCD_REV()                                (g_stDisplayDPTxInfo.ucDPCDRev)
#define SET_DISPLAY_DP_TX_DPCD_REV(x)                               (g_stDisplayDPTxInfo.ucDPCDRev = (x))

#define GET_DISPLAY_DP_TX_LINK_RATE()                               (g_stDisplayDPTxInfo.ucLinkRate)
#define SET_DISPLAY_DP_TX_LINK_RATE(x)                              (g_stDisplayDPTxInfo.ucLinkRate = (x))

#define GET_DISPLAY_DP_TX_LANE_NUM()                                (g_stDisplayDPTxInfo.b3LaneNum)
#define SET_DISPLAY_DP_TX_LANE_NUM(x)                               (g_stDisplayDPTxInfo.b3LaneNum = (x))

#define GET_DISPLAY_DP_TX_MAX_LINK_RATE()                           (g_stDisplayDPTxInfo.ucMaxLinkRate)
#define SET_DISPLAY_DP_TX_MAX_LINK_RATE(x)                          (g_stDisplayDPTxInfo.ucMaxLinkRate = (x))

#define GET_DISPLAY_DP_TX_ENHANCE_FRAMING()                         (g_stDisplayDPTxInfo.b1EnhanceFraming)
#define SET_DISPLAY_DP_TX_ENHANCE_FRAMING(x)                        (g_stDisplayDPTxInfo.b1EnhanceFraming = (x))

#define GET_DISPLAY_DP_TX_ALTERNATE_SR_CAPABLE()                    (g_stDisplayDPTxInfo.b1AlternateSrCapable)
#define SET_DISPLAY_DP_TX_ALTERNATE_SR_CAPABLE(x)                   (g_stDisplayDPTxInfo.b1AlternateSrCapable = (x))

#define GET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE()                  (g_stDisplayDPTxInfo.b1FramingChangeCapable)
#define SET_DISPLAY_DP_TX_FRAMING_CHANGE_CAPABLE(x)                 (g_stDisplayDPTxInfo.b1FramingChangeCapable = (x))

#define GET_DISPLAY_DP_TX_DOWN_SPREAD()                             (g_stDisplayDPTxInfo.b1SSCSupport)
#define SET_DISPLAY_DP_TX_DOWN_SPREAD(x)                            (g_stDisplayDPTxInfo.b1SSCSupport = (x))

#define GET_DISPLAY_DP_TX_TP3_SUPPORT()                             (g_stDisplayDPTxInfo.b1TP3Support)
#define SET_DISPLAY_DP_TX_TP3_SUPPORT()                             (g_stDisplayDPTxInfo.b1TP3Support = _TRUE)
#define CLR_DISPLAY_DP_TX_TP3_SUPPORT()                             (g_stDisplayDPTxInfo.b1TP3Support = _FALSE)

#define GET_DISPLAY_DP_TX_INFO_READY()                              (g_stDisplayDPTxInfo.b1DownStreamInfoReady)
#define SET_DISPLAY_DP_TX_INFO_READY()                              (g_stDisplayDPTxInfo.b1DownStreamInfoReady = _TRUE)
#define CLR_DISPLAY_DP_TX_INFO_READY()                              (g_stDisplayDPTxInfo.b1DownStreamInfoReady = _FALSE)

//--------------------------------------------------
// Macros of DP Tx Input Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TX_INPUT_COLOR_DEPTH()                       (g_stDisplayDPTxInputInfo.b3ColorDepth)
#define SET_DISPLAY_DP_TX_INPUT_COLOR_DEPTH(x)                      (g_stDisplayDPTxInputInfo.b3ColorDepth = (x))

#define GET_DISPLAY_DP_TX_INPUT_COLOR_SPACE()                       (g_stDisplayDPTxInputInfo.b3ColorSpace)
#define SET_DISPLAY_DP_TX_INPUT_COLOR_SPACE(x)                      (g_stDisplayDPTxInputInfo.b3ColorSpace = (x))

#define GET_DISPLAY_DP_TX_INPUT_PIXEL_CLK()                         (g_stDisplayDPTxInputInfo.usInputPixelClk)
#define SET_DISPLAY_DP_TX_INPUT_PIXEL_CLK(x)                        (g_stDisplayDPTxInputInfo.usInputPixelClk = (x))
#define CLR_DISPLAY_DP_TX_INPUT_PIXEL_CLK()                         (g_stDisplayDPTxInputInfo.usInputPixelClk = 0)

#define GET_DISPLAY_DP_TX_LINK_CONFIG()                             (g_stDisplayDPTxInputInfo.b1LinkConfig)
#define SET_DISPLAY_DP_TX_LINK_CONFIG(x)                            (g_stDisplayDPTxInputInfo.b1LinkConfig = (x))

//--------------------------------------------------
// Macros of DP Tx Link Infomation
//--------------------------------------------------
#define GET_DISPLAY_DP_TX_LT_STATE()                                (g_stDisplayDPTxLTInfo.b2LinkTrainingState)
#define SET_DISPLAY_DP_TX_LT_STATE(x)                               (g_stDisplayDPTxLTInfo.b2LinkTrainingState = (x))

#define GET_DISPLAY_DP_TX_LT_RESULT()                               (g_stDisplayDPTxLTInfo.b4LinkTrainingResult)
#define SET_DISPLAY_DP_TX_LT_RESULT(x)                              (g_stDisplayDPTxLTInfo.b4LinkTrainingResult = (x))

#define GET_DISPLAY_DP_TX_LINK_PBN_PER_TIMESOLT()                   (g_stDisplayDPTxLTInfo.ucLinkPBNPerTimeSlot)
#define SET_DISPLAY_DP_TX_LINK_PBN_PER_TIMESOLT(x)                  (g_stDisplayDPTxLTInfo.ucLinkPBNPerTimeSlot = (x))

#define GET_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane0SameVolCnt)
#define ADD_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane0SameVolCnt++)
#define CLR_DISPLAY_DP_TX_TP1_LANE0_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane0SameVolCnt = 0)

#define GET_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane1SameVolCnt)
#define ADD_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane1SameVolCnt++)
#define CLR_DISPLAY_DP_TX_TP1_LANE1_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane1SameVolCnt = 0)

#define GET_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane2SameVolCnt)
#define ADD_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane2SameVolCnt++)
#define CLR_DISPLAY_DP_TX_TP1_LANE2_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane2SameVolCnt = 0)

#define GET_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane3SameVolCnt)
#define ADD_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane3SameVolCnt++)
#define CLR_DISPLAY_DP_TX_TP1_LANE3_SAME_VOL_CNT()                  (g_stDisplayDPTxLTInfo.b3TP1Lane3SameVolCnt = 0)

#define GET_DISPLAY_DP_TX_TP2_CNT()                                 (g_stDisplayDPTxLTInfo.b3TP2count)
#define ADD_DISPLAY_DP_TX_TP2_CNT()                                 (g_stDisplayDPTxLTInfo.b3TP2count++)
#define CLR_DISPLAY_DP_TX_TP2_CNT()                                 (g_stDisplayDPTxLTInfo.b3TP2count = 0)

#define GET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING()                 (g_stDisplayDPTxLTInfo.ucLane0Adjust & 0x03)
#define SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING(x)                (g_stDisplayDPTxLTInfo.ucLane0Adjust = ((g_stDisplayDPTxLTInfo.ucLane0Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane0Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane0Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING()                 (g_stDisplayDPTxLTInfo.ucLane1Adjust & 0x03)
#define SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING(x)                (g_stDisplayDPTxLTInfo.ucLane1Adjust = ((g_stDisplayDPTxLTInfo.ucLane1Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane1Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane1Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING()                 (g_stDisplayDPTxLTInfo.ucLane2Adjust & 0x03)
#define SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING(x)                (g_stDisplayDPTxLTInfo.ucLane2Adjust = ((g_stDisplayDPTxLTInfo.ucLane2Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane2Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane2Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING()                 (g_stDisplayDPTxLTInfo.ucLane3Adjust & 0x03)
#define SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING(x)                (g_stDisplayDPTxLTInfo.ucLane3Adjust = ((g_stDisplayDPTxLTInfo.ucLane3Adjust & 0xFC) | (x)))
#define SET_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane3Adjust |= _BIT2)
#define CLR_DISPLAY_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH()       (g_stDisplayDPTxLTInfo.ucLane3Adjust &= ~_BIT2)

#define GET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()              ((g_stDisplayDPTxLTInfo.ucLane0Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(x)             (g_stDisplayDPTxLTInfo.ucLane0Adjust = ((g_stDisplayDPTxLTInfo.ucLane0Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane0Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane0Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()              ((g_stDisplayDPTxLTInfo.ucLane1Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(x)             (g_stDisplayDPTxLTInfo.ucLane1Adjust = ((g_stDisplayDPTxLTInfo.ucLane1Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane1Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane1Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()              ((g_stDisplayDPTxLTInfo.ucLane2Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(x)             (g_stDisplayDPTxLTInfo.ucLane2Adjust = ((g_stDisplayDPTxLTInfo.ucLane2Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane2Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane2Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()              ((g_stDisplayDPTxLTInfo.ucLane3Adjust & (_BIT4 | _BIT3)) >> 3)
#define SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(x)             (g_stDisplayDPTxLTInfo.ucLane3Adjust = ((g_stDisplayDPTxLTInfo.ucLane3Adjust & ~(_BIT4 | _BIT3)) | ((x) << 3)))
#define SET_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane3Adjust |= _BIT5)
#define CLR_DISPLAY_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH()    (g_stDisplayDPTxLTInfo.ucLane3Adjust &= ~_BIT5)

#define GET_DISPLAY_DP_TX_LANE0_CR_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane01LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX_LANE1_CR_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane01LTStatus & _BIT4) == _BIT4)
#define GET_DISPLAY_DP_TX_LANE2_CR_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane23LTStatus & _BIT0) == _BIT0)
#define GET_DISPLAY_DP_TX_LANE3_CR_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane23LTStatus & _BIT4) == _BIT4)

#define GET_DISPLAY_DP_TX_LANE0_EQ_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX_LANE1_EQ_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_DISPLAY_DP_TX_LANE2_EQ_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_DISPLAY_DP_TX_LANE3_EQ_DONE()                           ((g_stDisplayDPTxLTInfo.ucLane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_DISPLAY_DP_TX_LANE_ALIGN_DONE()                         ((g_stDisplayDPTxLTInfo.ucLaneAlignStatus & _BIT0) == _BIT0)

#define GET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING()                  (g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX_LANE0_ADJUST_VOL_SWING(x)                 (g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING()                  ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX_LANE1_ADJUST_VOL_SWING(x)                 (g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING()                  (g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & (_BIT1 | _BIT0))
#define SET_DISPLAY_DP_TX_LANE2_ADJUST_VOL_SWING(x)                 (g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & ~(_BIT1 | _BIT0)) | (x)))

#define GET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING()                  ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_DISPLAY_DP_TX_LANE3_ADJUST_VOL_SWING(x)                 (g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & ~(_BIT5 | _BIT4)) | ((x) << 4)))

#define GET_DISPLAY_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()               ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define SET_DISPLAY_DP_TX_LANE0_ADJUST_PRE_EMPHASIS(x)              (g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DISPLAY_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()               ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define SET_DISPLAY_DP_TX_LANE1_ADJUST_PRE_EMPHASIS(x)              (g_stDisplayDPTxLTInfo.ucAdjustReqLane01 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane01 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

#define GET_DISPLAY_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()               ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define SET_DISPLAY_DP_TX_LANE2_ADJUST_PRE_EMPHASIS(x)              (g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & ~(_BIT3 | _BIT2)) | ((x) << 2)))

#define GET_DISPLAY_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()               ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & (_BIT7 | _BIT6)) >> 6)
#define SET_DISPLAY_DP_TX_LANE3_ADJUST_PRE_EMPHASIS(x)              (g_stDisplayDPTxLTInfo.ucAdjustReqLane23 = ((g_stDisplayDPTxLTInfo.ucAdjustReqLane23 & ~(_BIT7 | _BIT6)) | ((x) << 6)))

#endif // End of #if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayDPTxSSCSet(bit bSscEn);

#if(_PANEL_DPTX_LINK_RATE != _PANEL_DPTX_LINK_HBR2)
extern void ScalerDisplayDPTxPhy(bit bOn);
extern void ScalerDisplayDPTxPLL(bit bOn);
extern void ScalerDisplayDPTxPower(bit bOn);
extern void ScalerDisplayDPTxSetLinkRate(void);

#if(_DISPLAY_DP_TX_PORT_1 == _ON)
extern void ScalerDisplayDPTx1AuxInitial(void);
extern void ScalerDisplayDPTx1AuxPHYSet(BYTE ucMode);
extern bit ScalerDisplayDPTx1AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx1AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDisplayDPTx1HpdInitial(void);
extern void ScalerDisplayDPTx1SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDPTx1SignalInitialSetting(void);
extern void ScalerDisplayDPTx1LanePowerOff(void);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDPTx1SetTp2PatternType(void);
#endif // End of #if(_DISPLAY_DP_TX_PORT_1 == _ON)

#if(_DISPLAY_DP_TX_PORT_2 == _ON)
extern void ScalerDisplayDPTx2AuxInitial(void);
extern void ScalerDisplayDPTx2AuxPHYSet(BYTE ucMode);
extern bit ScalerDisplayDPTx2AuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
extern bit ScalerDisplayDPTx2AuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
extern void ScalerDisplayDPTx2HpdInitial(void);
extern void ScalerDisplayDPTx2SetSignalLevel(EnumDisplayDPTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
extern void ScalerDisplayDPTx2SignalInitialSetting(void);
extern void ScalerDisplayDPTx2LanePowerOff(void);
extern EnumDisplayDPTxTrainPattern ScalerDisplayDPTx2SetTp2PatternType(void);
extern void ScalerDisplayDPTx2SetTps3PatternMux(bit bAphyMux);
#endif // End of #if(_DISPLAY_DP_TX_PORT_2 == _ON)

#else
extern void ScalerDisplayDPTxInitial(void);
#endif
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

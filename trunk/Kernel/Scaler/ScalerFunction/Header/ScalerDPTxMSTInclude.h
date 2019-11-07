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
// ID Code      : ScalerDPTxMSTInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

//****************************************************************************
// LAYER DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// Definitions of RD Buffer Status
//--------------------------------------------------
#define _DP_I2C_MAX_TRANSACTION_LENGTH                              16
#define _DP_TX_AUX_WRITE_BURST_LENGTH                               0x0F
#define _DP_TX_AUX_READ_BURST_LENGTH                                0x0F

//--------------------------------------------------
// Macro of Downstream MSG Block
//--------------------------------------------------
#define SET_REG_DP_TX_DOWNSTREAM_MSG_AUTO_MODE()                    (ScalerSetBit(PBD_B5_MSG_WR_CTRL, ~_BIT2, 0x00))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_ENABLE()                 (ScalerSetBit(PBD_B5_MSG_WR_CTRL, ~_BIT0, _BIT0))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_DISABLE()                (ScalerSetBit(PBD_B5_MSG_WR_CTRL, ~_BIT0, 0x00))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_BURST_LENGTH(x)                (ScalerSetByte(PBD_B8_MSG_WR_BUR_LENGTH, ((x) & 0x0F)))
#define SET_REG_DP_TX_DOWNSTREAM_TO_DOWN_REQUEST_ADDRESS()          (ScalerSetBit(PBD_C3_MSG_WR_ADR_SEL, ~_BIT0, 0x00))
#define SET_REG_DP_TX_DOWNSTREAM_TO_UP_REPLY_ADDRESS()              (ScalerSetBit(PBD_C3_MSG_WR_ADR_SEL, ~_BIT0, _BIT0))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_LCT(x)                         (ScalerSetBit(PBD_B9_MSG_WR_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ((x) << 4)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_LCR(x)                         (ScalerSetBit(PBD_B9_MSG_WR_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_BROADCAST(x)                   (ScalerSetBit(PBD_C1_MSG_WR_SET8, ~_BIT7, ((x) << 7)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_PATH(x)                        (ScalerSetBit(PBD_C1_MSG_WR_SET8, ~_BIT6, ((x) << 6)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_MSN(x)                         (ScalerSetBit(PBD_C2_MSG_WR_SET9, ~_BIT4, ((x) << 4)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(x)                      (ScalerSetByte(PBD_B7_MSG_WR_LENGTH, (x)))
#define GET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH()                       (ScalerGetByte(PBD_B7_MSG_WR_LENGTH))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_PTR(x)                   (ScalerSetByte(PBD_C6_BUF_FW_WRPTR, ((x) & 0x3F)))
#define SET_REG_DP_TX_DOWNSTREAM_MSG_DATA(x)                        (ScalerSetByte(PBD_C7_BUF_FW_WR_DATA, (x)))
#define CLR_REG_DP_TX_DOWNSTREAM_MSG_BUF()                          (ScalerSetBit(PBD_C5_BUF_CLR, ~_BIT0, _BIT0))
#define CLR_REG_DP_TX_DOWNSTREAM_MSG_WRITE_FINISH_FLAG()            (ScalerSetBit(PBD_B6_MSG_WR_FINISH, ~_BIT0, _BIT0))

//--------------------------------------------------
// Macro of Upstream MSG Block
//--------------------------------------------------
#define SET_REG_DP_TX_UPSTREAM_MSG_READ_ENABLE()                    (ScalerSetBit(PBD_CA_AUX_TX_MSG_RD_CTRL, ~_BIT0, _BIT0))
#define SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE()                   (ScalerSetBit(PBD_CA_AUX_TX_MSG_RD_CTRL, ~_BIT0, 0x00))
#define SET_REG_DP_TX_UPSTREAM_MSG_READ_BURST_LENGTH(x)             (ScalerSetByte(PBD_CE_MSG_RD_BUR_LENGTH, (_BIT4 | ((x) & 0x0F))))
#define SET_REG_DP_TX_UPSTREAM_MSG_READ_PTR(x)                      (ScalerSetByte(PBD_DC_MSG_BUF_RDPTR, ((x) & 0x3F)))
#define SET_REG_DP_TX_UPSTREAM_MSG_T0_DOWN_REPLY_ADDRESS()          (ScalerSetBit(PBD_DA_MSG_RD_ADR_SEL, ~_BIT0, 0x00))
#define SET_REG_DP_TX_UPSTREAM_MSG_TO_UP_REQUEST_ADDRESS()          (ScalerSetBit(PBD_DA_MSG_RD_ADR_SEL, ~_BIT0, _BIT0))
#define GET_REG_DP_TX_UPSTREAM_MSG_LCT()                            (ScalerGetBit(PBD_CF_MSG_RD_DATA0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)))
#define GET_REG_DP_TX_UPSTREAM_MSG_LCR()                            (ScalerGetBit(PBD_CF_MSG_RD_DATA0, (_BIT3 | _BIT2 | _BIT1 | _BIT0)))
#define GET_REG_DP_TX_UPSTREAM_MSG_BROADCAST()                      (ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT7))
#define GET_REG_DP_TX_UPSTREAM_MSG_PATH()                           (ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT6))
#define GET_REG_DP_TX_UPSTREAM_MSG_MSN()                            (ScalerGetBit(PBD_D8_MSG_RD_DATA9, _BIT4))
#define GET_REG_DP_TX_UPSTREAM_MSG_LENGTH()                         (ScalerGetByte(PBD_CD_MSG_RD_LENGTH))
#define GET_REG_DP_TX_UPSTREAM_MSG_READ_DATA()                      (ScalerGetByte(PBD_DD_MSG_BUF_RD_DATA))
#define GET_REG_DP_TX_UPSTREAM_MSG_READ_FINISH()                    (ScalerGetBit(PBD_CC_MSG_RD_FINISH, _BIT0))
#define CLR_REG_DP_TX_UPSTREAM_MSG_READ_FINISH_FLAG()               (ScalerSetBit(PBD_CC_MSG_RD_FINISH, ~(_BIT1 | _BIT0), _BIT0))
#define CLR_REG_DP_TX_UPSTREAM_SBMSG_FINISH_FLAG()                  (ScalerSetBit(PBD_CC_MSG_RD_FINISH, ~(_BIT1 | _BIT0), _BIT1))
#define GET_REG_DP_TX_UPSTREM_MSG_CRC_STATUS()                      (ScalerGetBit(PBD_DB_MSG_RD_FLAG, (_BIT1 | _BIT0)))
#define GET_REG_DP_TX_UPSTREM_MSG_HEADER_CRC_STATUS()               ((bit)ScalerGetBit(PBD_DB_MSG_RD_FLAG, _BIT1))
#define GET_REG_DP_TX_UPSTREAM_SBMSG_START_OF_BIT()                 ((bit)ScalerGetBit(PBD_D8_MSG_RD_DATA9, _BIT7))
#define GET_REG_DP_TX_UPSTREAM_SBMSG_END_OF_BIT()                   ((bit)ScalerGetBit(PBD_D8_MSG_RD_DATA9, _BIT6))
#define CLR_REG_DP_TX_UPSTREAM_MSG_BUF()                            (ScalerSetBit(PBD_DE_MSG_BUF_CLR, ~_BIT0, _BIT0))

//--------------------------------------------------
// Macro of QUERY STREAM ENCRYPTION STATUS
//--------------------------------------------------
#define SET_REG_DP_TX_SHA_ENABLE()                                  (ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, 0x00))
#define CLR_REG_DP_TX_SHA_ENABLE()                                  (ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, _BIT1))
#define SET_REG_DP_TX_SHA_INPUT_0(x)                                (ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, (x)))
#define SET_REG_DP_TX_SHA_INPUT_1(x)                                (ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, (x)))
#define SET_REG_DP_TX_SHA_INPUT_2(x)                                (ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, (x)))
#define SET_REG_DP_TX_SHA_INPUT_3(x)                                (ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, (x)))
#define SET_REG_DP_TX_SHA_INPUT_DB()                                (ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0))
#define GET_REG_DP_TX_HDCP_AN(x)                                    (ScalerGetByte(PBB_3B_AN_BYTE_0 - (x)))
#define GET_REG_DP_TX_HDCP_M0(x)                                    (ScalerGetByte(PBB_43_M0_BYTE_0 - (x)))
#define GET_REG_DP_TX_HDCP_BKSV(x)                                  (ScalerGetByte(PBB_4F_BKSV_0 + (x)))

#define GET_DP_TX_HDCP_ENCRYPTION_ENABLE()                          (ScalerGetBit(PBB_30_DPTX_HDCP_CTRL1, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
#define GET_DP_TX_HDCP_AUTH_PROC_PASS()                             (GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_AUTH_PASS)

//--------------------------------------------------
// Macro of Message Function Action info
//--------------------------------------------------
#define GET_DP_TX_DOWN_REQUEST_READY()                              (g_stTxMsgFunction.b1DownRequestReady)
#define SET_DP_TX_DOWN_REQUEST_READY()                              (g_stTxMsgFunction.b1DownRequestReady = _TRUE)
#define CLR_DP_TX_DOWN_REQUEST_READY()                              (g_stTxMsgFunction.b1DownRequestReady = _FALSE)

#define GET_DP_TX_DOWN_REQUEST_ANAL()                               (g_stTxMsgFunction.b1DownRequestAnal)
#define SET_DP_TX_DOWN_REQUEST_ANAL()                               (g_stTxMsgFunction.b1DownRequestAnal = _TRUE)
#define CLR_DP_TX_DOWN_REQUEST_ANAL()                               (g_stTxMsgFunction.b1DownRequestAnal = _FALSE)

#define GET_DP_TX_DOWN_REPLY_READY()                                (g_stTxMsgFunction.b1DownReplyReady)
#define SET_DP_TX_DOWN_REPLY_READY()                                (g_stTxMsgFunction.b1DownReplyReady = _TRUE)
#define CLR_DP_TX_DOWN_REPLY_READY()                                (g_stTxMsgFunction.b1DownReplyReady = _FALSE)

#define GET_DP_TX_DOWN_REPLY_ANAL()                                 (g_stTxMsgFunction.b1DownReplyAnal)
#define SET_DP_TX_DOWN_REPLY_ANAL()                                 (g_stTxMsgFunction.b1DownReplyAnal = _TRUE)
#define CLR_DP_TX_DOWN_REPLY_ANAL()                                 (g_stTxMsgFunction.b1DownReplyAnal = _FALSE)

#define GET_DP_TX_DOWN_REPLY_DIRECTLY()                             (g_stTxMsgFunction.b1DownReplyDirect)
#define SET_DP_TX_DOWN_REPLY_DIRECTLY()                             (g_stTxMsgFunction.b1DownReplyDirect = _TRUE)
#define CLR_DP_TX_DOWN_REPLY_DIRECTLY()                             (g_stTxMsgFunction.b1DownReplyDirect = _FALSE)

#define GET_DP_TX_DOWN_REPLY_READ_DISABLE()                         (g_stTxMsgFunction.b1DownReplyReadDisable)
#define SET_DP_TX_DOWN_REPLY_READ_DISABLE()                         (g_stTxMsgFunction.b1DownReplyReadDisable = _TRUE)
#define CLR_DP_TX_DOWN_REPLY_READ_DISABLE()                         (g_stTxMsgFunction.b1DownReplyReadDisable = _FALSE)

#define GET_DP_TX_UP_REQUEST_READY()                                (g_stTxMsgFunction.b1UpRequestReady)
#define SET_DP_TX_UP_REQUEST_READY()                                (g_stTxMsgFunction.b1UpRequestReady = _TRUE)
#define CLR_DP_TX_UP_REQUEST_READY()                                (g_stTxMsgFunction.b1UpRequestReady = _FALSE)

#define GET_DP_TX_UP_REQUEST_ANAL()                                 (g_stTxMsgFunction.b1UpRequestAnal)
#define SET_DP_TX_UP_REQUEST_ANAL()                                 (g_stTxMsgFunction.b1UpRequestAnal = _TRUE)
#define CLR_DP_TX_UP_REQUEST_ANAL()                                 (g_stTxMsgFunction.b1UpRequestAnal = _FALSE)

#define GET_DP_TX_UP_REPLY_READY()                                  (g_stTxMsgFunction.b1UpReplyReady)
#define SET_DP_TX_UP_REPLY_READY()                                  (g_stTxMsgFunction.b1UpReplyReady = _TRUE)
#define CLR_DP_TX_UP_REPLY_READY()                                  (g_stTxMsgFunction.b1UpReplyReady = _FALSE)

#define GET_DP_TX_UP_REPLY_BYPASS()                                 (g_stTxMsgFunction.b1UpReplyBypass)
#define SET_DP_TX_UP_REPLY_BYPASS()                                 (g_stTxMsgFunction.b1UpReplyBypass = _TRUE)
#define CLR_DP_TX_UP_REPLY_BYPASS()                                 (g_stTxMsgFunction.b1UpReplyBypass = _FALSE)

#define GET_DP_TX_UP_REPLY_DIRECTLY()                               (g_stTxMsgFunction.b1UpReplyDirect)
#define SET_DP_TX_UP_REPLY_DIRECTLY()                               (g_stTxMsgFunction.b1UpReplyDirect = _TRUE)
#define CLR_DP_TX_UP_REPLY_DIRECTLY()                               (g_stTxMsgFunction.b1UpReplyDirect = _FALSE)

//--------------------------------------------------
// Macro of Message Block info
//--------------------------------------------------
#define GET_DP_TX_RD_BUFFER_STATUS()                                (g_stTxMsgInfo.b2RdBufferStatus)
#define SET_DP_TX_RD_BUFFER_STATUS(x)                               (g_stTxMsgInfo.b2RdBufferStatus = (x))

#define GET_DP_TX_DOWN_REQUEST_BROAD_MSG()                          (g_stTxMsgInfo.b1DownRequestBroadcastProc)
#define SET_DP_TX_DOWN_REQUEST_BROAD_MSG()                          (g_stTxMsgInfo.b1DownRequestBroadcastProc = _TRUE)
#define CLR_DP_TX_DOWN_REQUEST_BROAD_MSG()                          (g_stTxMsgInfo.b1DownRequestBroadcastProc = _FALSE)

#define GET_DP_TX_DOWN_REQUEST_MSG_DONE()                           (g_stTxMsgInfo.b1DownRequestMsgDone)
#define SET_DP_TX_DOWN_REQUEST_MSG_DONE()                           (g_stTxMsgInfo.b1DownRequestMsgDone = _TRUE)
#define CLR_DP_TX_DOWN_REQUEST_MSG_DONE()                           (g_stTxMsgInfo.b1DownRequestMsgDone = _FALSE)

#define GET_DP_TX_UP_REPLY_MSG_DONE()                               (g_stTxMsgInfo.b1UpReplyMsgDone)
#define SET_DP_TX_UP_REPLY_MSG_DONE()                               (g_stTxMsgInfo.b1UpReplyMsgDone = _TRUE)
#define CLR_DP_TX_UP_REPLY_MSG_DONE()                               (g_stTxMsgInfo.b1UpReplyMsgDone = _FALSE)

#define GET_DP_TX_SELF_GEN_UP_REQUEST_MSG()                         (g_stTxMsgInfo.b1SelfGenUpRequest)
#define SET_DP_TX_SELF_GEN_UP_REQUEST_MSG()                         (g_stTxMsgInfo.b1SelfGenUpRequest = _TRUE)
#define CLR_DP_TX_SELF_GEN_UP_REQUEST_MSG()                         (g_stTxMsgInfo.b1SelfGenUpRequest = _FALSE)

#define GET_DP_TX_UP_REQUEST_BYPASS_REGEN()                         (g_stTxMsgInfo.b1UpRequestBypassRegen)
#define SET_DP_TX_UP_REQUEST_BYPASS_REGEN()                         (g_stTxMsgInfo.b1UpRequestBypassRegen = _TRUE)
#define CLR_DP_TX_UP_REQUEST_BYPASS_REGEN()                         (g_stTxMsgInfo.b1UpRequestBypassRegen = _FALSE)

#define GET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG()                        (g_stTxMsgInfo.b1IllegalDownRequestMSG)
#define SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG()                        (g_stTxMsgInfo.b1IllegalDownRequestMSG = _TRUE)
#define CLR_DP_TX_ILLEGAL_DOWN_REQUEST_MSG()                        (g_stTxMsgInfo.b1IllegalDownRequestMSG = _FALSE)

#define GET_DP_TX_ILLEGAL_UP_REQUEST_MSG()                          (g_stTxMsgInfo.b1IllegalUpRequestMSG)
#define SET_DP_TX_ILLEGAL_UP_REQUEST_MSG()                          (g_stTxMsgInfo.b1IllegalUpRequestMSG = _TRUE)
#define CLR_DP_TX_ILLEGAL_UP_REQUEST_MSG()                          (g_stTxMsgInfo.b1IllegalUpRequestMSG = _FALSE)

#define GET_DP_GEN_UP_REQUEST_MSG()                                 (g_stTxMsgInfo.ucGenUpRequestMsg)
#define SET_DP_GEN_UP_REQUEST_MSG(x)                                (g_stTxMsgInfo.ucGenUpRequestMsg = (x))
#define CLR_DP_GEN_UP_REQUEST_MSG()                                 (g_stTxMsgInfo.ucGenUpRequestMsg = _DP_MSG_NONE)

#define GET_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()        (g_stTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone)
#define SET_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()        (g_stTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone = _TRUE)
#define CLR_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE()        (g_stTxMsgInfo.b1DownReplyBroadcastDirectlyReplyDone = _FALSE)

#define GET_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()          (g_stTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg)
#define SET_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()          (g_stTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg = _TRUE)
#define CLR_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE()          (g_stTxMsgInfo.b1WaitClearPayloadIdTableDownReplyMsg = _FALSE)

//--------------------------------------------------
// Macro of Event Processor info
//--------------------------------------------------

#define GET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                    (g_stTxEventProcInfo.b1MsgDownReqAnalFinish)
#define SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                    (g_stTxEventProcInfo.b1MsgDownReqAnalFinish = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH()                    (g_stTxEventProcInfo.b1MsgDownReqAnalFinish = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH()                      (g_stTxEventProcInfo.b1MsgDownRepAnalFinish)
#define SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH()                      (g_stTxEventProcInfo.b1MsgDownRepAnalFinish = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH()                      (g_stTxEventProcInfo.b1MsgDownRepAnalFinish = _FALSE)

//--------------------------------------------------
//Others
//--------------------------------------------------

#define GET_DP_TX_DOWN_REQUEST_EVENT()                              (g_stTxEventProcInfo.b4MsgDownReqEventType)
#define SET_DP_TX_DOWN_REQUEST_EVENT(x)                             (g_stTxEventProcInfo.b4MsgDownReqEventType = (x))
#define GET_DP_TX_DOWN_REPLY_EVENT()                                (g_stTxEventProcInfo.b4MsgDownRepEventType)
#define SET_DP_TX_DOWN_REPLY_EVENT(x)                               (g_stTxEventProcInfo.b4MsgDownRepEventType = (x))


//--------------------------------------------------
//DownReply SBMSG Interleave Macro
//--------------------------------------------------
#define GET_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()                 (g_stTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply)
#define SET_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()                 (g_stTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE()                 (g_stTxMsgInterleaveInfo.b1SidebandMsgInterLeaveReply = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf0CrcFailure = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE()                 (g_stTxMsgInterleaveInfo.b1DownReplyBuf1CrcFailure = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf0Finish)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf0Finish = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf0Finish = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf1Finish)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf1Finish = _TRUE)
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH()                  (g_stTxMsgInterleaveInfo.b1DownReplyBuf1Finish = _FALSE)

#define GET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT()               (g_stTxMsgInterleaveInfo.ucDownReplyStartCount)
#define SET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT(x)              (g_stTxMsgInterleaveInfo.ucDownReplyStartCount = (x))
#define CLR_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT()               (g_stTxMsgInterleaveInfo.ucDownReplyStartCount = 0)

#define GET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT()                 (g_stTxMsgInterleaveInfo.ucDownReplyEndCount)
#define SET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(x)                (g_stTxMsgInterleaveInfo.ucDownReplyEndCount = (x))
#define CLR_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT()                 (g_stTxMsgInterleaveInfo.ucDownReplyEndCount = 0)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH()                 (g_stTxMsgInterleaveInfo.ucDownReplyBuf0DataLength)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(x)                (g_stTxMsgInterleaveInfo.ucDownReplyBuf0DataLength = (x))
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH()                 (g_stTxMsgInterleaveInfo.ucDownReplyBuf0DataLength = 0)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH()                 (g_stTxMsgInterleaveInfo.ucDownReplyBuf1DataLength)
#define SET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(x)                (g_stTxMsgInterleaveInfo.ucDownReplyBuf1DataLength = (x))
#define CLR_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH()                 (g_stTxMsgInterleaveInfo.ucDownReplyBuf1DataLength = 0)

#define GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA(x)                       (g_pucDownReplyBuf0Data[x])
#define SET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA(x, y)                    (g_pucDownReplyBuf0Data[x] = (y))

#define GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA(x)                       (g_pucDownReplyBuf1Data[x])
#define SET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA(x, y)                    (g_pucDownReplyBuf1Data[x] = (y))


//--------------------------------------------------
// Definitions of Tx Receipt Msg Count Macro
//--------------------------------------------------
#define GET_DP_TX_RECEIVED_MSG_COUNT()                              (g_ucDPTxReceivedMsgCount)
#define SET_DP_TX_RECEIVED_MSG_COUNT(x)                             (g_ucDPTxReceivedMsgCount = (x))


#define GET_DP_TX_DOWN_REQUEST_BODY_LENGTH()                        (g_ucDPDownReqBodyLength)
#define SET_DP_TX_DOWN_REQUEST_BODY_LENGTH(x)                       (g_ucDPDownReqBodyLength = (x))

#define GET_DP_TX_UP_REPLY_BODY_LENGTH()                            (g_ucDPUpRepBodyLength)
#define SET_DP_TX_UP_REPLY_BODY_LENGTH(x)                           (g_ucDPUpRepBodyLength = (x))

//Connection Status Notify MSG
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(x)            (g_unDpRequestPool.stConnectionStatusNotify.b4PortNum = (x))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_GUID(x, y)             (g_unDpRequestPool.stConnectionStatusNotify.pucGUID[x] = (y))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(x)    (g_unDpRequestPool.stConnectionStatusNotify.b3PeerDeviceType = (x))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_INPUT_PORT(x)          (g_unDpRequestPool.stConnectionStatusNotify.b1InputPort = (x))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(x)             (g_unDpRequestPool.stConnectionStatusNotify.b1MsgCabability = (x))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_DP_PLUG_STATUS(x)      (g_unDpRequestPool.stConnectionStatusNotify.b1DpPlugStatus = (x))
#define GET_DP_REQUEST_MSG_CONNECTION_STATUS_DP_PLUG_STATUS()       (g_unDpRequestPool.stConnectionStatusNotify.b1DpPlugStatus)
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(x)  (g_unDpRequestPool.stConnectionStatusNotify.b1LegacyPlugStatus = (x))
#define SET_DP_REQUEST_MSG_CONNECTION_STATUS_ZEROS()                {\
                                                                        g_unDpRequestPool.stConnectionStatusNotify.b1Zero = 0;\
                                                                        g_unDpRequestPool.stConnectionStatusNotify.b4Zero1 = 0;\
                                                                        g_unDpRequestPool.stConnectionStatusNotify.b1Zero2 = 0;\
                                                                    }

//Resource Status Notify MSG
#define SET_DP_REQUEST_MSG_RESOURCE_STATUS_PORT_NUM(x)              (g_unDpRequestPool.stStructReqResourceStatusNotify.b4PortNum = (x))
#define SET_DP_REQUEST_MSG_RESOURCE_STATUS_GUID(x, y)               (g_unDpRequestPool.stStructReqResourceStatusNotify.pucGUID[x] = (y))
#define SET_DP_REQUEST_MSG_RESOURCE_STATUS_AVAILABLE_PBN(x)         (g_unDpRequestPool.stStructReqResourceStatusNotify.usAvailablePBN = (x))
#define SET_DP_REQUEST_MSG_RESORUCE_STATUS_ZEROS()                  {\
                                                                        g_unDpRequestPool.stStructReqResourceStatusNotify.b1Zero = 0;\
                                                                        g_unDpRequestPool.stStructReqResourceStatusNotify.b4Zero1 = 0;\
                                                                    }

#define SET_DP_MSG_REQUEST_ID(x)                                    (g_unDpRequestPool.pucData[0] = (x))

#define GET_DP_TX_UP_REQUEST_BACKUP_DATA(x)                         (g_pucUpRequestBackUp[x])
#define SET_DP_TX_UP_REQUEST_BACKUP_DATA(x, y)                      (g_pucUpRequestBackUp[x] = (y))
#define CLR_DP_TX_UP_REQUEST_BACKUP_DATA()                          (memset(g_pucUpRequestBackUp, 0, sizeof(g_pucUpRequestBackUp)))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//--------------------------------------------------
// Enumerations of DP Tx Event Which Result From Message
//--------------------------------------------------
typedef enum
{
    _DP_TX_NONE_EVENT,
    _DP_TX_SYNC_PAYLOAD_TABLE,
    _DP_TX_CLEAR_ID_TABLE,
    _DP_TX_POWER_UP,
    _DP_TX_POWER_DOWN,
    _DP_TX_DPCD_READ,
    _DP_TX_DPCD_WRITE ,
    _DP_TX_I2C_READ,
    _DP_TX_I2C_WRITE,
    _DP_TX_ENUM_PATH,
    _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS,
} EnumTxEventType;

typedef enum
{
    _DP_TX_READ_BUF_EMPTY,
    _DP_TX_READ_BUF_DOWN_REPLY_IN_USE,
    _DP_TX_READ_BUF_UP_REQUEST_IN_USE,
} EnumTxReadBufferStatus;

typedef enum
{
    // MSG Header
    _UP_REQ_BACK_UP_LCT,
    _UP_REQ_BACK_UP_LCR,
    _UP_REQ_BACK_UP_BROADCAST,
    _UP_REQ_BACK_UP_PATH,
    _UP_REQ_BACK_UP_MSG_LENGTH,
    _UP_REQ_BACK_UP_MSG_MSN,

    // MSG Body (General)
    _UP_REQ_BACK_UP_MSG_ID,
    _UP_REQ_BACK_UP_PORT_NUM,
    _UP_REQ_BACK_UP_GUID_1,
    _UP_REQ_BACK_UP_GUID_2,
    _UP_REQ_BACK_UP_GUID_3,
    _UP_REQ_BACK_UP_GUID_4,
    _UP_REQ_BACK_UP_GUID_5,
    _UP_REQ_BACK_UP_GUID_6,
    _UP_REQ_BACK_UP_GUID_7,
    _UP_REQ_BACK_UP_GUID_8,
    _UP_REQ_BACK_UP_GUID_9,
    _UP_REQ_BACK_UP_GUID_10,
    _UP_REQ_BACK_UP_GUID_11,
    _UP_REQ_BACK_UP_GUID_12,
    _UP_REQ_BACK_UP_GUID_13,
    _UP_REQ_BACK_UP_GUID_14,
    _UP_REQ_BACK_UP_GUID_15,
    _UP_REQ_BACK_UP_GUID_16,

    // MSG Body (Connection Status Notify)
    _UP_REQ_BACK_UP_LEGACY_STATUS,
    _UP_REQ_BACK_UP_DP_STATUS,
    _UP_REQ_BACK_UP_MSG_CAP_STATUS,
    _UP_REQ_BACK_UP_INPUT_PORT,
    _UP_REQ_BACK_UP_PEER_DEV_TYPE,
/*
    // MSG Body (Resource Status Notify)
    _UP_REQ_BACK_UP_AVAILABLE_PBN_H,
    _UP_REQ_BACK_UP_AVAILABLE_PBN_L,
*/
    _UP_REQ_BACK_UP_DPCD_200_STATUS,
} EnumUpRequestBackUp;

//--------------------------------------------------
// Struct for Message Function Action Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DownRequestAnal : 1;
    BYTE b1DownReplyDirect : 1;
    BYTE b1DownReplyAnal : 1;
    BYTE b1UpRequestAnal : 1;
    BYTE b1UpReplyBypass : 1;
    BYTE b1UpReplyDirect : 1;
    BYTE b1DownRequestReady : 1;
    BYTE b1DownReplyReady : 1;
    BYTE b1DownReplyReadDisable : 1;
    BYTE b1UpRequestReady : 1;
    BYTE b1UpReplyReady : 1;
}StructTxMsgFunctionInfo;

//--------------------------------------------------
// Struct for Message Info
//--------------------------------------------------
typedef struct
{
    BYTE b1DownRequestMsgDone : 1;
    BYTE b1UpReplyMsgDone : 1;
    BYTE b1SelfGenUpRequest : 1;
    BYTE b1UpRequestBypassRegen : 1;
    BYTE b2RdBufferStatus : 2;
    BYTE b1DownRequestBroadcastProc : 1;
    BYTE b1IllegalDownRequestMSG : 1;
    BYTE b1IllegalUpRequestMSG : 1;
    BYTE ucGenUpRequestMsg;
    BYTE b1DownReplyBroadcastDirectlyReplyDone : 1;
    BYTE b1WaitClearPayloadIdTableDownReplyMsg : 1;
}StructTxMsgInfo;



//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
//--------------------------------------------------
// Struct for Event Processor Info
//--------------------------------------------------
typedef struct
{
    BYTE b1MsgDownReqAnalFinish : 1;
    BYTE b4MsgDownReqEventType : 4;
    BYTE b1MsgDownRepAnalFinish : 1;
    BYTE b4MsgDownRepEventType : 4;
}StructTxEventProcInfo;


//--------------------------------------------------
// Struct for Tx Header Backup
//--------------------------------------------------
typedef struct
{
    BYTE b4MsgLct : 4;
    BYTE b4MsgLcr : 4;
    BYTE pucMsgRad[7];
    BYTE b1MsgBroadcast : 1;
    BYTE b1MsgPath : 1;
    BYTE b1MsgMsn : 1;
    BYTE ucWritePtr;
}StructTxDownReplyMsgInterleaveHeaderInfo;

//--------------------------------------------------
// Struct for Tx Header Backup
//--------------------------------------------------
typedef struct
{
    BYTE b1SidebandMsgInterLeaveReply : 1;
    BYTE b1DownReplyBuf0CrcFailure : 1;
    BYTE b1DownReplyBuf1CrcFailure : 1;
    BYTE b1DownReplyBuf0Finish : 1;
    BYTE b1DownReplyBuf1Finish : 1;
    BYTE ucDownReplyStartCount;
    BYTE ucDownReplyEndCount;
    BYTE ucDownReplyBuf0DataLength;
    BYTE ucDownReplyBuf1DataLength;
}StructTxDownReplyMsgInterleaveInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructTxMsgFunctionInfo g_stTxMsgFunction;
extern StructTxMsgInfo g_stTxMsgInfo;
extern StructTxEventProcInfo g_stTxEventProcInfo;
extern BYTE g_ucDPDownReqBodyLength;
extern BYTE g_ucDPUpRepBodyLength;
extern BYTE g_ucDPTxReceivedMsgCount;
extern BYTE g_pucUpRequestBackUp[30];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
//extern void ScalerDpTxMonitorDownstreamBW(void);
extern void ScalerDpTxMstMsgCountResetEvent(void);
extern void ScalerDpTxMstReset(void);

#endif // End of #if((_DP_TX_SUPPORT == _ON) && (_DP_MST_SUPPORT == _ON))

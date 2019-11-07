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
// ID Code      : ScalerDPTxMST.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTXMST__

#include "ScalerFunctionInclude.h"

#if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructTxMsgFunctionInfo g_stTxMsgFunction;
StructTxMsgInfo g_stTxMsgInfo;
StructTxEventProcInfo g_stTxEventProcInfo;
BYTE g_ucDPDownReqBodyLength;
BYTE g_ucDPUpRepBodyLength;
BYTE g_ucDPTxReceivedMsgCount;

// For SBMSG Interleave Case
StructTxDownReplyMsgInterleaveHeaderInfo g_stTxMsgBackupHeaderInfo0;
StructTxDownReplyMsgInterleaveHeaderInfo g_stTxMsgBackupHeaderInfo1;
StructTxDownReplyMsgInterleaveInfo g_stTxMsgInterleaveInfo;
BYTE g_pucDownReplyBuf0Data[259];
BYTE g_pucDownReplyBuf1Data[259];
BYTE g_pucUpRequestBackUp[30];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerDpTxMstHandler(void);
void ScalerDpTxMstDownRequestProc(void);
void ScalerDpTxMstDownReplyProc(void);
void ScalerDpTxMstDownRequestAnal(void);
void ScalerDpTxMstDownReplyAnal(void);
void ScalerDpTxMstUpRequestProc(void);
void ScalerDpTxMstUpReplyProc(void);
void ScalerDpTxMstUpRequestAnal(void);
void ScalerDpTxMstUpReplyAnal(void);
void ScalerDpTxMstDownRequestEventProc(void);
void ScalerDpTxMstDownReplyEventProc(void);
bit ScalerDpTxMstWriteMsgToDownstreamStatusCheck(EnumDpMessageType enumMsgType);
void ScalerDpTxMstDownRequestHeaderModify(void);
bit ScalerDpTxMstDownRequestMsgAnal(void);
bit ScalerDpTxMstSyncDownStreamTableSetting(BYTE ucPayloadID, BYTE ucStartPosition, BYTE ucLength);
void ScalerDpTxMstDownReplyDirectlyMsg(void);
bit ScalerDpTxMstGetDownReplyCrcFailed(void);
BYTE ScalerDpTxMstGetDownReplyLct(void);
BYTE ScalerDpTxMstGetDownReplyLcr(void);
bit ScalerDpTxMstGetDownReplyBroadcastBit(void);
bit ScalerDpTxMstGetDownReplyPathBit(void);
bit ScalerDpTxMstGetDownReplyMsn(void);
BYTE ScalerDpTxMstGetDownReplyLength(void);
void ScalerDpTxMstDownReplyBypassHeaderModify(void);
void ScalerDpTxMstDownReplyBypass(void);
bit ScalerDpTxMstSyncTableProcess(BYTE ucPayloadID, WORD usPBN);
//void ScalerDpTxMonitorDownstreamBW(void);
//void ScalerDpTxLocalRecoveryPayloadTable(BYTE ucCurrentPBNPerTimerslot);
WORD ScalerDpTxMstGetAvailablePBN(void);
void ScalerDpTxMstModifyRAD(EnumDpMessageType enumMsgType);
void ScalerDpTxMstIllegalMsgReply(void);
bit ScalerDpTxMstI2CRead(void);
bit ScalerDpTxMstI2CWrite(void);
void ScalerDpTxMstMsgCountResetEvent(void);
void ScalerDpTxMstQueryEncryptionWriteShaInput(void);
BYTE ScalerDpTxMstQueryEncryptionGetShaResult(BYTE ucIndex);
bit ScalerDpTxMstQueryEncryptionCompareShaResult(void);
void ScalerDpTxMstDownReplyHeaderBackUp(StructTxDownReplyMsgInterleaveHeaderInfo *pstTxDownReplyMsgHeaderInfo);
bit ScalerDpTxMstDownReplySidebandMsgHeaderCheck(StructTxDownReplyMsgInterleaveHeaderInfo stTxDownReplyMsgHeaderInfo);
void ScalerDpTxMstDownReplySideBandMsgProc(void);
void ScalerDpTxMstDownReplyInterleaveFinishCheck(void);
void ScalerDpTxMstClrDownReplyInterleaveFlag(void);
void ScalerDpTxMstReset(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Mst Msg Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstHandler(void)
{
    if(g_enumDpMSTCapablePort == _DP_MST_NO_PORT)
    {
        return;
    }

    ScalerDpTxMstDownRequestAnal();
    ScalerDpTxMstDownRequestEventProc();
    ScalerDpTxMstDownRequestProc();

    ScalerDpTxMstDownReplyProc();
    ScalerDpTxMstDownReplyAnal();
    ScalerDpTxMstDownReplyEventProc();

    ScalerDpTxMstUpRequestProc();
    ScalerDpTxMstUpRequestAnal();

    ScalerDpTxMstUpReplyAnal();
    ScalerDpTxMstUpReplyProc();
}

//--------------------------------------------------
// Description  : DP Tx Processor for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownRequestProc(void)
{
    if(GET_DP_TX_DOWN_REQUEST_READY() == _TRUE)
    {
        CLR_DP_TX_DOWN_REQUEST_READY();

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Reset FIFO
        SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_PTR(0x00);

        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Disable Defer/TimeOut/Nack/Error Retry Machine
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        // Move Array Data to Buffer
        for(pData[0] = 0; pData[0] < GET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(); pData[0]++)
        {
            SET_REG_DP_TX_DOWNSTREAM_MSG_DATA(GET_DP_MSG_REQUEST_ARRAY(pData[0]));
        }

        // Make Sure Down Request has Been Propagated
        if(ScalerDpTxMstWriteMsgToDownstreamStatusCheck(_DP_DOWN_REQUEST_MSG) == _TRUE)
        {
            if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
            {
                SET_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
            }

            // Count DownRequest Msg
            if(GET_DP_TX_RECEIVED_MSG_COUNT() < 255)
            {
                SET_DP_TX_RECEIVED_MSG_COUNT(GET_DP_TX_RECEIVED_MSG_COUNT() + 1);
            }

            ScalerTimerReactiveTimerEvent(SEC(4), _SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
        }

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

        SET_DP_TX_DOWN_REQUEST_MSG_DONE();
    }
}

//--------------------------------------------------
// Description  : DP Tx Processor for Down Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyProc(void)
{
    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == _DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ)
    {
        SET_DP_TX_DOWN_REPLY_READY();
    }

    // Down Reply Ready IRQ_HPD Received and Read Buffer is not used by Up Request
    if((GET_DP_TX_DOWN_REPLY_READY() == _TRUE) && (GET_DP_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_UP_REQUEST_IN_USE) && (GET_DP_TX_DOWN_REPLY_READ_DISABLE() == _FALSE))
    {
        CLR_DP_TX_DOWN_REPLY_READY();

        if(GET_DP_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_EMPTY)
        {
            // CLR MSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_MSG_READ_FINISH_FLAG();

            // CLR SBMSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_SBMSG_FINISH_FLAG();

            // Buf_CLR=1 WR_PTR = 0x00
            CLR_REG_DP_TX_UPSTREAM_MSG_BUF();

            SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_DOWN_REPLY_IN_USE);

            ScalerDpTxMstClrDownReplyInterleaveFlag();
        }

        // Select to DownReply Address
        SET_REG_DP_TX_UPSTREAM_MSG_T0_DOWN_REPLY_ADDRESS();

        // Enable Defer/TimeOut/Nack/Error Retry Machine
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Disable AUX FW Handle Mode
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, 0x00);

        // Start RD MSG circuit
        SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();
        SET_REG_DP_TX_UPSTREAM_MSG_READ_ENABLE();

        if(ScalerTimerPollingFlagProc(100, PBD_CC_MSG_RD_FINISH, _BIT1, _TRUE) == _TRUE)
        {
            // Disable Defer/TimeOut/Nack/Error Retry Machine
            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Tx Read MSG
            SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();

            // Enable AUX FW Handle Mode
            ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);

            // CLR SBMSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_SBMSG_FINISH_FLAG();

            // CLR DownReply Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);

            // CLR DownStream DPCD DownReply Ready Bit
            pData[0] = _BIT4;
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x03, 1, pData);

            ScalerDpTxMstDownReplySideBandMsgProc();
        }
        else
        {
            // CLR DownReply Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);

            SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

            // Disable Defer/TimeOut/Nack/Error Retry Machine
            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Tx Read MSG
            SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();

            // Enable AUX FW Handle Mode
            ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);
        }

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
    }

    if(GET_DP_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_DOWN_REPLY_IN_USE)
    {
        if(((GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) || (GET_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH() == _TRUE)) &&
           (GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
        {
            CLR_DP_REPLY_POOL_FREE();

            // Disable Reply Buffer Free
            CLR_DP_RX_REPLY_BUF_FREE();

            // Move full MSG from RD Buffer to Array
            for(pData[0] = 0; pData[0] < ((GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) ?
                                          GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() : GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH()); pData[0]++)
            {
                SET_DP_MSG_REPLY_ARRAY(pData[0], ((GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) ?
                                                  GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA(pData[0]) : GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA(pData[0])));
            }

            if(GET_DP_MSG_REPLY_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE)
            {
                CLR_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
            }

            SET_DP_TX_DOWN_REPLY_ANAL();

            // Delete DownRequest Msg Count
            if(GET_DP_TX_RECEIVED_MSG_COUNT() > 0)
            {
                SET_DP_TX_RECEIVED_MSG_COUNT(GET_DP_TX_RECEIVED_MSG_COUNT() - 1);
            }

            if(GET_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE() == _TRUE)
            {
                if((GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0) || (GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0))
                {
                    SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
                }
            }
            else
            {
                SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownRequestAnal(void)
{
    if(GET_DP_TX_DOWN_REQUEST_ANAL() == _TRUE)
    {
        // Tx Down Req MSG Anal
        if(ScalerDpTxMstDownRequestMsgAnal() == _TRUE)
        {
            // CLR Flag
            CLR_DP_TX_DOWN_REQUEST_ANAL();
        }
    }

    // Tx Event processor finish, check result is sucessful or fail
    if(GET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

        if((GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
        {
            if(GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _FALSE)
            {
                // Modify DP Tx WR MSG header based on DP Rx RD MSG header
                ScalerDpTxMstDownRequestHeaderModify();

                if(GET_DP_TX_DOWN_REQUEST_BROAD_MSG() == _FALSE)
                {
                    // Release Down Request Buffer
                    SET_DP_RX_DOWN_REQ_BUF_RELEASE();

                    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();
                }
            }

            // Bypass Down Request MSG
            SET_DP_TX_DOWN_REQUEST_READY();
        }
        else if(GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
        {
            SET_DP_TX_DOWN_REQUEST_READY();
        }
        else
        {
            if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
            {
                if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
                {
                    // Modify DP Tx WR MSG header based on DP Rx RD MSG header
                    ScalerDpTxMstDownRequestHeaderModify();

                    // Release Down Request Buffer
                    SET_DP_RX_DOWN_REQ_BUF_RELEASE();

                    CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

                    // Bypass Down Request MSG
                    SET_DP_TX_DOWN_REQUEST_READY();
                }
                else
                {
                    SET_DP_TX_DOWN_REPLY_DIRECTLY();
                }
            }
            else
            {
                SET_DP_TX_DOWN_REPLY_DIRECTLY();
            }
        }
    }

    if(GET_DP_TX_DOWN_REQUEST_MSG_DONE() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_DOWN_REQUEST_MSG_DONE();

        if(GET_DP_TX_DOWN_REQUEST_BROAD_MSG() == _TRUE)
        {
            // Clr flag
            CLR_DP_TX_DOWN_REQUEST_BROAD_MSG();

            if(GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
            {
                // Clr flag
                CLR_DP_RX_SELF_GEN_DOWN_REQUEST_MSG();

                // Release Request Array Free
                SET_DP_REQUEST_POOL_FREE();
            }
            else
            {
                SET_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE();
            }
        }
        else
        {
            // Release Request Array Free
            SET_DP_REQUEST_POOL_FREE();
        }
    }

    if((GET_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
    {
        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        // Disable Reply Buffer Free
        CLR_DP_RX_REPLY_BUF_FREE();

        CLR_DP_TX_DOWN_REPLY_BROADCAST_DIRECTLY_REPLY_DONE();

        SET_DP_TX_DOWN_REPLY_DIRECTLY();
    }
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Down Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyAnal(void)
{
    if(GET_DP_TX_DOWN_REPLY_DIRECTLY() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_DOWN_REPLY_DIRECTLY();

        // Message Reply
        ScalerDpTxMstDownReplyDirectlyMsg();

        // Release Down Request Buffer
        SET_DP_RX_DOWN_REQ_BUF_RELEASE();

        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

        // Free Request Array
        SET_DP_REQUEST_POOL_FREE();

        SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
    }

    if(GET_DP_TX_DOWN_REPLY_ANAL() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_DOWN_REPLY_ANAL();

        // Check MSG CRC
        if(ScalerDpTxMstGetDownReplyCrcFailed() == _FALSE)
        {
            if(ScalerDpTxMstGetDownReplyBroadcastBit() == _FALSE)
            {
                ScalerDpTxMstDownReplyBypass();

                // Modify Header Info.
                ScalerDpTxMstDownReplyBypassHeaderModify();

//================================================For Interleave case===================================
                if(GET_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE() == _TRUE)
                {
                    ScalerDpTxMstDownReplyInterleaveFinishCheck();
                }
                else
                {
                    // TX Read Enable
                    CLR_DP_TX_DOWN_REPLY_READ_DISABLE();

                    CLR_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();
                }
//================================================For Interleave case===================================
            }
            else
            {
                SET_DP_REPLY_POOL_FREE();

                // Free Reply Buffer
                SET_DP_RX_REPLY_BUF_FREE();

                // TX Read Enable
                CLR_DP_TX_DOWN_REPLY_READ_DISABLE();
            }
        }
        else
        {
            SET_DP_REPLY_POOL_FREE();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();

            // TX Read Enable
            CLR_DP_TX_DOWN_REPLY_READ_DISABLE();
        }
    }


    if((GET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
    {
        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        // Disable Reply Buffer Free
        CLR_DP_RX_REPLY_BUF_FREE();

        // CLR Flag
        CLR_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();

        // Error Reply
        ScalerDpRxMstIllegalMsgReply();

        // Release Down Request Buffer
        SET_DP_RX_DOWN_REQ_BUF_RELEASE();

        CLR_REG_DP_RX_DOWN_REQUEST_ADDR_WRITTEN();

        // Free Request Array
        SET_DP_REQUEST_POOL_FREE();

        SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
    }

    if(GET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();

        SET_DP_RX_DOWN_REPLY_BYPASS();
    }
}

//--------------------------------------------------
// Description  : DP Tx Processor for Up Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstUpRequestProc(void)
{
    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == _DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ)
    {
        SET_DP_TX_UP_REQUEST_READY();
    }

    // Up Request Ready IRQ_HPD Received and Read Buffer is not used by Down Reply
    if((GET_DP_TX_UP_REQUEST_READY() == _TRUE) && (GET_DP_TX_RD_BUFFER_STATUS() != _DP_TX_READ_BUF_DOWN_REPLY_IN_USE) && (GET_DP_TX_DOWN_REPLY_READ_DISABLE() == _FALSE))
    {
        CLR_DP_TX_UP_REQUEST_READY();

        if(GET_DP_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_EMPTY)
        {
            // CLR MSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_MSG_READ_FINISH_FLAG();

            // CLR SBMSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_SBMSG_FINISH_FLAG();

            // Buf_CLR=1 WR_PTR=0x00
            CLR_REG_DP_TX_UPSTREAM_MSG_BUF();
        }

        // Select to Up Request Address
        SET_REG_DP_TX_UPSTREAM_MSG_TO_UP_REQUEST_ADDRESS();

        // Enable Defer/TimeOut/Nack/Error Retry Machine
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Disable AUX FW Handle Mode
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, 0x00);

        // Start RD MSG circuit
        SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();
        SET_REG_DP_TX_UPSTREAM_MSG_READ_ENABLE();

        if(ScalerTimerPollingFlagProc(100, PBD_CC_MSG_RD_FINISH, _BIT1, _TRUE) == _TRUE)
        {
            // Disable Defer/TimeOut/Nack/Error Retry Machine
            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Tx Read MSG
            SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();

            // Enable AUX FW Handle Mode
            ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);

            // CLR SBMSG Finish Flag
            CLR_REG_DP_TX_UPSTREAM_SBMSG_FINISH_FLAG();

            // CLR Up Request Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);

            // CLR DownStream DPCD Up Request Ready Bit
            pData[0] = _BIT5;
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x03, 1, pData);

            SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_UP_REQUEST_IN_USE);

            if(GET_REG_DP_TX_UPSTREAM_MSG_READ_FINISH() == _TRUE)
            {
                SET_DP_TX_DOWN_REPLY_READ_DISABLE();
            }
        }
        else // Read MSG Failed
        {
            // CLR Up Request Ready Flag
            CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);

            SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

            // Disable Defer/TimeOut/Nack/Error Retry Machine
            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Tx Read MSG
            SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();

            // Enable AUX FW Handle Mode
            ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);
        }

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
    }

    if(GET_DP_TX_RD_BUFFER_STATUS() == _DP_TX_READ_BUF_UP_REQUEST_IN_USE)
    {
        if((GET_REG_DP_TX_UPSTREAM_MSG_READ_FINISH() == _TRUE) && (GET_DP_REQUEST_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
        {
            // Occupy Request Pool
            CLR_DP_REQUEST_POOL_FREE();

            // Disable Reply Buffer Free
            CLR_DP_RX_REPLY_BUF_FREE();

            // CLR Flag
            CLR_REG_DP_TX_UPSTREAM_MSG_READ_FINISH_FLAG();

            // BUF_READ_PTR = 0
            SET_REG_DP_TX_UPSTREAM_MSG_READ_PTR(0x00);

            // Get Up Request MSG and Using Requeset Pool to Analysis
            for(pData[0] = 0; pData[0] < GET_REG_DP_TX_UPSTREAM_MSG_LENGTH(); pData[0]++)
            {
                SET_DP_MSG_REQUEST_ARRAY(pData[0], GET_REG_DP_TX_UPSTREAM_MSG_READ_DATA());
            }

            SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

            //========== Set Next Action ==============

            // Dp Tx Self Analize Received Up_Request MSG
            SET_DP_TX_UP_REQUEST_ANAL();
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Processor for Up Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstUpReplyProc(void)
{
    if(GET_DP_TX_UP_REPLY_READY() == _TRUE)
    {
        CLR_DP_TX_UP_REPLY_READY();

        // Disable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

        // Move MSG body from Array to DP Tx WR Buffer
        SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_PTR(0x00);

        // Move Array Data to Buffer
        for(pData[0] = 0; pData[0] < GET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(); pData[0]++)
        {
            SET_REG_DP_TX_DOWNSTREAM_MSG_DATA(GET_DP_MSG_REPLY_ARRAY(pData[0]));
        }

        ScalerDpTxMstWriteMsgToDownstreamStatusCheck(_DP_UP_REPLY_MSG);

        // Enable Short HPD Int.
        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

        SET_DP_TX_UP_REPLY_MSG_DONE();
    }
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Up Request MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstUpRequestAnal(void)
{
    // Receive Up Request From Downstream
    if(GET_DP_TX_UP_REQUEST_ANAL() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_UP_REQUEST_ANAL();

        if(GET_DP_MST_RX_CABLE_STATUS() == _TRUE)
        {
            // CRC OK
            if(GET_REG_DP_TX_UPSTREM_MSG_CRC_STATUS() == (_BIT1 | _BIT0))
            {
                switch(GET_DP_MSG_REQUEST_ID())
                {
                    case _DP_MSG_CONNECTION_STATUS_NOTIFY:

                        // In MST mode, Bit2 : STREAM_STATUS_CHANGED is set to 1 if DPTX connect a new downstream device.
                        // Indicates the source must re-check the Stream Status with the QUERY_STREAM_ENCRYPTION_STATUS message.
                        SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x05, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x05) | _BIT2));

                        if((GET_REG_DP_TX_UPSTREAM_MSG_LCR() > 0) && ((GET_REG_DP_TX_UPSTREAM_MSG_LCR() - 1) >= GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR)))
                        {
                            if(GET_DP_TX_SELF_GEN_UP_REQUEST_MSG() == _FALSE)
                            {
                                // Let Rx Bypass Up Request
                                SET_DP_TX_UP_REQUEST_BYPASS_REGEN();
                            }

                            CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

                            // ---------BackUp Msg Header---------

                            // Set LCT = 1
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT, GET_REG_DP_TX_UPSTREAM_MSG_LCT());

                            // Set LCR = 6
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR, (GET_REG_DP_TX_UPSTREAM_MSG_LCR() - 1));

                            // Set Broadcast and Path Bit
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST, GET_REG_DP_TX_UPSTREAM_MSG_BROADCAST());
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH, GET_REG_DP_TX_UPSTREAM_MSG_PATH());

                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_MSN, GET_REG_DP_TX_UPSTREAM_MSG_MSN());

                            // Set MSG Body Length
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_LENGTH, GET_REG_DP_TX_UPSTREAM_MSG_LENGTH());

                            if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
                            {
                                // Initiate Connection Status Notify
                                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);

                                // ---------BackUp Msg Body---------

                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID, (GET_DP_MSG_REQUEST_ARRAY(0) & 0x7F));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM, ((GET_DP_MSG_REQUEST_ARRAY(1) & 0xF0) >> 4));
#if(_DP_SUPPORT == _ON)
                                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                                {
                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0], GET_DP_MSG_REQUEST_ARRAY(2 + pData[0]));
                                }
#endif
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LEGACY_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT6) >> 6));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DP_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT5) >> 5));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_CAP_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT4) >> 4));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_INPUT_PORT, _DP_OUTPUT_PORT);
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PEER_DEV_TYPE, (GET_DP_MSG_REQUEST_ARRAY(18) & 0x07));

                                if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DP_STATUS) == _TRUE)
                                {
                                    // Read Sink Count
                                    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, pData);

                                    // Set Rx Sink Count
                                    pData[1] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);

                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DPCD_200_STATUS, pData[1]);

                                    pData[1] = (pData[1] & 0xC0) | ((pData[0] & 0x3F) + 1);

                                    SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[1]);
                                }
                            }
/*
                            else if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_RESOURCE_STATUS_NOTIFY)
                            {
                                // Initiate Resource Status Notify
                                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);

                                // ---------BackUp Msg Body---------

                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID, (GET_DP_MSG_REQUEST_ARRAY(0) & 0x7F));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM, ((GET_DP_MSG_REQUEST_ARRAY(1) & 0xF0) >> 4));

#if(_DP_SUPPORT == _ON)
                                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                                {
                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0], GET_DP_MSG_REQUEST_ARRAY(2 + pData[0]));
                                }
#endif
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_H, GET_DP_MSG_REQUEST_ARRAY(18));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_L, GET_DP_MSG_REQUEST_ARRAY(19));
                            }
*/
                            // Release Request Pool
                            SET_DP_REQUEST_POOL_FREE();

                            // Set Reply Buffer Free
                            SET_DP_RX_REPLY_BUF_FREE();
                        }
                        else
                        {
                            // Reply ACK to Downstream
                            SET_DP_TX_UP_REPLY_DIRECTLY();

                            // Free Reply Buffer
                            SET_DP_RX_REPLY_BUF_FREE();
                        }

                        break;

                    case _DP_MSG_RESOURCE_STATUS_NOTIFY:

                        if((GET_REG_DP_TX_UPSTREAM_MSG_LCR() > 0) && ((GET_REG_DP_TX_UPSTREAM_MSG_LCR() - 1) >= GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR)))
                        {
                            if(GET_DP_TX_SELF_GEN_UP_REQUEST_MSG() == _FALSE)
                            {
                                // Let Rx Bypass Up Request
                                SET_DP_TX_UP_REQUEST_BYPASS_REGEN();
                            }

                            CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

                            // ---------BackUp Msg Header---------

                            // Set LCT = 1
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT, GET_REG_DP_TX_UPSTREAM_MSG_LCT());

                            // Set LCR = 6
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR, (GET_REG_DP_TX_UPSTREAM_MSG_LCR() - 1));

                            // Set Broadcast and Path Bit
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST, GET_REG_DP_TX_UPSTREAM_MSG_BROADCAST());
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH, GET_REG_DP_TX_UPSTREAM_MSG_PATH());

                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_MSN, GET_REG_DP_TX_UPSTREAM_MSG_MSN());

                            // Set MSG Body Length
                            SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_LENGTH, GET_REG_DP_TX_UPSTREAM_MSG_LENGTH());

                            if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
                            {
                                // Initiate Connection Status Notify
                                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);

                                // ---------BackUp Msg Body---------

                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID, (GET_DP_MSG_REQUEST_ARRAY(0) & 0x7F));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM, ((GET_DP_MSG_REQUEST_ARRAY(1) & 0xF0) >> 4));
#if(_DP_SUPPORT == _ON)
                                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                                {
                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0], GET_DP_MSG_REQUEST_ARRAY(2 + pData[0]));
                                }
#endif
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LEGACY_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT6) >> 6));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DP_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT5) >> 5));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_CAP_STATUS, ((GET_DP_MSG_REQUEST_ARRAY(18) & _BIT4) >> 4));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_INPUT_PORT, _DP_OUTPUT_PORT);
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PEER_DEV_TYPE, (GET_DP_MSG_REQUEST_ARRAY(18) & 0x07));

                                if(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DP_STATUS) == _TRUE)
                                {
                                    // Read Sink Count
                                    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, pData);

                                    // Set Rx Sink Count
                                    pData[1] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);

                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DPCD_200_STATUS, pData[1]);

                                    pData[1] = (pData[1] & 0xC0) | ((pData[0] & 0x3F) + 1);

                                    SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[1]);
                                }
                            }
/*
                            else if(GET_DP_MSG_REQUEST_ID() == _DP_MSG_RESOURCE_STATUS_NOTIFY)
                            {
                                // Initiate Resource Status Notify
                                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);

                                // ---------BackUp Msg Body---------

                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID, (GET_DP_MSG_REQUEST_ARRAY(0) & 0x7F));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM, ((GET_DP_MSG_REQUEST_ARRAY(1) & 0xF0) >> 4));

#if(_DP_SUPPORT == _ON)
                                for(pData[0] = 0; pData[0] < 16; pData[0]++)
                                {
                                    SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0], GET_DP_MSG_REQUEST_ARRAY(2 + pData[0]));
                                }
#endif
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_H, GET_DP_MSG_REQUEST_ARRAY(18));
                                SET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_L, GET_DP_MSG_REQUEST_ARRAY(19));
                            }
*/
                            // Release Request Pool
                            SET_DP_REQUEST_POOL_FREE();

                            // Set Reply Buffer Free
                            SET_DP_RX_REPLY_BUF_FREE();
                        }
                        else
                        {
                            // Reply ACK to Downstream
                            SET_DP_TX_UP_REPLY_DIRECTLY();

                            // Free Reply Buffer
                            SET_DP_RX_REPLY_BUF_FREE();
                        }

                        break;

                    default:

                        // ID Failure
                        SET_DP_TX_ILLEGAL_UP_REQUEST_MSG();

                        // Free Reply Buffer
                        SET_DP_RX_REPLY_BUF_FREE();

                        break;
                }
            }
            else
            {
                // CRC Failure
                SET_DP_TX_ILLEGAL_UP_REQUEST_MSG();

                // Free Reply Buffer
                SET_DP_RX_REPLY_BUF_FREE();
            }
        }
        else
        {
            // Free Request Pool
            SET_DP_REQUEST_POOL_FREE();

            // Free Reply Buffer
            SET_DP_RX_REPLY_BUF_FREE();
        }

        // TX Read Enable
        CLR_DP_TX_DOWN_REPLY_READ_DISABLE();
    }

    if(GET_DP_MST_RX_CABLE_STATUS() == _TRUE)
    {
        if((GET_DP_REQUEST_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
        {
            switch(GET_DP_GEN_UP_REQUEST_MSG())
            {
                case _DP_MSG_CONNECTION_STATUS_NOTIFY:

                    // Occupy Reply Pool
                    CLR_DP_REQUEST_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_RX_REPLY_BUF_FREE();

                    CLR_DP_GEN_UP_REQUEST_MSG();

                    // In MST mode, Bit2 : STREAM_STATUS_CHANGED is set to 1 if DPTX connect a new downstream device.
                    // Indicates the source must re-check the Stream Status with the QUERY_STREAM_ENCRYPTION_STATUS message.
                    SET_REG_DP_DPCD_INFO(0x00, 0x20, 0x05, (GET_REG_DP_DPCD_INFO(0x00, 0x20, 0x05) | _BIT2));

                    if(GET_DP_TX_UP_REQUEST_BYPASS_REGEN() == _TRUE)
                    {
                        //========== Set MSG Header ==============

                        // Set LCT = 1
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT));

                        // Set LCR = 6
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR));

                        // Set Broadcast and Path Bit
                        SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST));
                        SET_REG_DP_RX_UPSTREAM_REPLY_PATH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH));

                        // Set MSG Body Length
                        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_LENGTH));

                        //========== Set MSG Body ==============

                        SET_DP_MSG_REQUEST_ID(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM));

#if(_DP_SUPPORT == _ON)
                        for(pData[0] = 0; pData[0] < 16; pData[0]++)
                        {
                            SET_DP_REQUEST_MSG_CONNECTION_STATUS_GUID(pData[0], GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0]));
                        }
#endif
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LEGACY_STATUS));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_DP_PLUG_STATUS(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_DP_STATUS));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_CAP_STATUS));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_INPUT_PORT(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_INPUT_PORT));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PEER_DEV_TYPE));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_ZEROS();
                    }
                    else
                    {
                        SET_DP_TX_SELF_GEN_UP_REQUEST_MSG();

                        //========== Set MSG Header ==============

                        // Set LCT = 1
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCT((1 << 4));

                        // Set LCR = 6
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(0x06);

                        // Set Broadcast and Path Bit
                        SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(_ENABLE);
                        SET_REG_DP_RX_UPSTREAM_REPLY_PATH(_DISABLE);

                        // Set MSG Body Length
                        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(19);

                        //========== Set MSG Body ==============

                        SET_DP_MSG_REQUEST_ID(_DP_MSG_CONNECTION_STATUS_NOTIFY);
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(_DP_PORT1);

#if(_DP_SUPPORT == _ON)
                        for(pData[0] = 0; pData[0] < 16; pData[0]++)
                        {
                            SET_DP_REQUEST_MSG_CONNECTION_STATUS_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
                        }
#endif
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_LEGACY_PLUG_STATUS(GET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS());
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_DP_PLUG_STATUS(GET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS());
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_MSG_CAP(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS());
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_INPUT_PORT(_DP_OUTPUT_PORT);
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_PEER_DEVICE_TYPE(GET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE());
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_ZEROS();
                    }

                    //========== Set Next Action ==============

                    // Call Dp Rx to Analize Received Up_Request MSG
                    SET_DP_RX_UP_REQUEST_ANAL();

                    break;

                /*
                case _DP_MSG_RESOURCE_STATUS_NOTIFY:

                    // Occupy Reply Pool
                    CLR_DP_REQUEST_POOL_FREE();

                    // Disable Reply Buffer Free
                    CLR_DP_RX_REPLY_BUF_FREE();

                    CLR_DP_GEN_UP_REQUEST_MSG();

                    if(GET_DP_TX_UP_REQUEST_BYPASS_REGEN() == _TRUE)
                    {
                        // ---------Set Msg Header---------

                        // Set LCT = 1
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT));

                        // Set LCR = 6
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCR));

                        // Set Broadcast and Path Bit
                        SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST));
                        SET_REG_DP_RX_UPSTREAM_REPLY_PATH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH));

                        // Set MSG Body Length
                        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_LENGTH));

                        // ---------Set Msg Body---------

                        SET_DP_MSG_REQUEST_ID(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID));
                        SET_DP_REQUEST_MSG_CONNECTION_STATUS_PORT_NUM(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PORT_NUM));

#if(_DP_SUPPORT == _ON)
                        for(pData[0] = 0; pData[0] < 16; pData[0]++)
                        {
                            SET_DP_REQUEST_MSG_CONNECTION_STATUS_GUID(pData[0], GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_GUID_1 + pData[0]));
                        }
#endif
                        SET_DP_REQUEST_MSG_RESOURCE_STATUS_AVAILABLE_PBN((GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_H) << 8) | (GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_AVAILABLE_PBN_L)));
                        SET_DP_REQUEST_MSG_RESORUCE_STATUS_ZEROS();
                    }
                    else
                    {
                        SET_DP_TX_SELF_GEN_UP_REQUEST_MSG();

                        // ---------Set Msg Header---------

                        // Set LCT = 1
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCT((1 << 4));

                        // Set LCR = 6
                        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(0x06);

                        // Set Broadcast and Path Bit
                        SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(_ENABLE);
                        SET_REG_DP_RX_UPSTREAM_REPLY_PATH(_DISABLE);

                        // Set MSG Body Length
                        SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(20);

                        // ---------Set Msg Body---------

                        SET_DP_MSG_REQUEST_ID(_DP_MSG_RESOURCE_STATUS_NOTIFY);
                        SET_DP_REQUEST_MSG_RESOURCE_STATUS_PORT_NUM(_DP_PORT1);

#if(_DP_SUPPORT == _ON)
                        for(pData[0] = 0; pData[0] < 16; pData[0]++)
                        {
                            SET_DP_REQUEST_MSG_RESOURCE_STATUS_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
                        }
#endif
                        SET_DP_REQUEST_MSG_RESOURCE_STATUS_AVAILABLE_PBN(ScalerDpTxMstGetAvailablePBN());
                        SET_DP_REQUEST_MSG_RESORUCE_STATUS_ZEROS();
                    }

                    //========== Set Next Action ==============

                    // Call Dp Rx to Analize Received Up_Request MSG
                    SET_DP_RX_UP_REQUEST_ANAL();

                    break;
                */
                default:
                    break;
            }
        }
    }
    else
    {
        if(GET_DP_GEN_UP_REQUEST_MSG() != _DP_MSG_NONE)
        {
            CLR_DP_GEN_UP_REQUEST_MSG();
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Analysis for Up Reply MSG
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstUpReplyAnal(void)
{
    if(GET_DP_TX_UP_REPLY_BYPASS() == _TRUE)
    {
        // CLR Flag
        CLR_DP_TX_UP_REPLY_BYPASS();

        //========== Set Next Action ==============

        // Dp Tx Bypass Rx Up_Reply MSG to Down Stream
        SET_DP_TX_UP_REPLY_READY();
    }

    if((GET_DP_TX_UP_REPLY_DIRECTLY() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE))
    {
        // CLR Flag
        CLR_DP_TX_UP_REPLY_DIRECTLY();

        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        //========== Body Info ==============

        SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REPLY_TYPE(_DP_MSG_ACK);

        SET_DP_REPLY_MSG_CONNECTION_STATUS_NOTIFY_REQUEST_ID(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID));

        //========== Header Info ==============
        // Set LCT = 1
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCT(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_LCT));

        // Set LCR = 0
        SET_REG_DP_TX_DOWNSTREAM_MSG_LCR(0);

        // Set Broadcast Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_BROADCAST(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_BROADCAST));

        // Set Path Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_PATH(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_PATH));

        // Set TX MSG Write Total Length
        SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(1);

        // Set MSN Bit
        SET_REG_DP_TX_DOWNSTREAM_MSG_MSN(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_MSN));

        //========== Release FW Memory ==============

        // Free Request Array
        SET_DP_REQUEST_POOL_FREE();

        // Clear Up_Req Bypass MSG Back Up
        CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

        //========== Set Next Action ==============

        // Dp Rx Directly Reply Up_Reply (Ack) MSG to Down Stream
        SET_DP_TX_UP_REPLY_READY();
    }

    if(GET_DP_TX_UP_REPLY_MSG_DONE() == _TRUE)
    {
        CLR_DP_TX_UP_REPLY_MSG_DONE();

        SET_DP_REPLY_POOL_FREE();
    }

    if((GET_DP_TX_ILLEGAL_UP_REQUEST_MSG() == _TRUE) && (GET_DP_REPLY_POOL_FREE() == _TRUE))
    {
        // CLR Flag
        CLR_DP_TX_ILLEGAL_UP_REQUEST_MSG();

        // Occupy Reply Pool
        CLR_DP_REPLY_POOL_FREE();

        // Set Reply Data
        ScalerDpTxMstIllegalMsgReply();

        //========== Release FW Memory ==============

        // Free Request Pool
        SET_DP_REQUEST_POOL_FREE();

        // Clear Up_Req Bypass MSG Back Up
        CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

        //========== Set Next Action ==============

        // Dp Tx Reply Illegal Up_Reply MSG to Down Stream
        SET_DP_TX_UP_REPLY_READY();
    }
}

//--------------------------------------------------
// Description  : Dp Tx Processor for Event
// Input Value  : ucEventType --> Event Type for Process
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownRequestEventProc(void)
{
    switch(GET_DP_TX_DOWN_REQUEST_EVENT())
    {
        case _DP_TX_SYNC_PAYLOAD_TABLE:

            if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
            {
                if((GET_DP_TX_STREAM_SOURCE_CHANGE() == _FALSE) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST))
                {
                    // Power Up Downstream
                    ScalerDpTxAuxNativeRead(0x00, 0x06, 0x00, 1, pData);

                    pData[0] = pData[0] & (_BIT2 | _BIT1 | _BIT0);

                    if((pData[0] == _BIT1) || (pData[0] == (_BIT2 | _BIT0)))
                    {
                        pData[0] = 0x01;
                        ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData);

                        SET_DP_TX_FORCE_LINK_TRAINING();

                        return;
                    }

                    if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 3, pData) == _TRUE)
                    {
                        if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pData[0] & 0x07) != 0x07)) ||
                           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pData[0] & 0x77) != 0x77)) ||
                           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pData[0] & 0x77) != 0x77) || ((pData[1] & 0x77) != 0x77))) ||
                           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pData[2] & 0x01) != 0x01)))
                        {
                            SET_DP_TX_FORCE_LINK_TRAINING();

                            return;
                        }
                    }

                    if(ScalerDpTxMstSyncTableProcess(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN()) == _TRUE)
                    {
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        // Table Sync Fail
                        // Linsp => Set Finish to Prevent Dead Lock
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                }
                else
                {
                    return;
                }
            }
            else
            {
                if(ScalerDpTxMstSyncTableProcess(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN()) == _TRUE)
                {
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    // Table Sync Fail
                    // Linsp => Set Finish to Prevent Dead Lock
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
            }

            break;

        case _DP_TX_CLEAR_ID_TABLE:

            if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
            {
                // Clear All ST3 ~ ST5 Time Slot
                for(pData[0] = 0; pData[0] < 3; pData[0]++)
                {
                    // CLR Daisy Chain Timeslot
                    ScalerSetBit((GET_DP_TX_STX_START_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }

                ScalerDpTxMstSyncDownStreamTableSetting(0x00, 0x00, 0x3F);
            }

            SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

            break;

        case _DP_TX_DPCD_READ:


            if(ScalerDpTxAuxNativeRead(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_H(),
                                       GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_M(),
                                       GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_ADDRESS_L(), GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ(), &SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_DATA(0)) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Failed to Readed

                // Linsp => Set Finish to Prevent Dead Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_DPCD_WRITE:

            if(ScalerDpTxAuxNativeWrite(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_H(),
                                        GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_M(),
                                        GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_ADDRESS_L(),
                                        GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_NUM_OF_WRITE(), &(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_DATA(0))) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Failed to Write

                // Linsp => Set Finish to Prevent Dead Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_I2C_READ:

            if(ScalerDpTxMstI2CRead() == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Avoid Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_I2C_WRITE:

            if(ScalerDpTxMstI2CWrite() == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Avoid Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_POWER_UP:

            pData[0] = 0x01;

            if(ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

                // Force Link Training
                SET_DP_TX_FORCE_LINK_TRAINING();
            }
            else
            {
                // Failed to Power up

                // Linsp => Set Finish to Prevent Dead Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_POWER_DOWN:

            pData[0] = 0x02;

            if(ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Failed to Power down

                // Linsp => Set Finish to Prevent Dead Lock
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        case _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS:

            SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

            break;

        default:
            break;
    }

    SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_NONE_EVENT);
}

//--------------------------------------------------
// Description  : Tx DownReply MSG Event Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyEventProc(void)
{
    switch(GET_DP_TX_DOWN_REPLY_EVENT())
    {
        case  _DP_TX_SYNC_PAYLOAD_TABLE:

            if(ScalerDpTxMstSyncTableProcess(GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(), GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN()) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }
            else
            {
                // Fail to Sync Table
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_TX_POWER_DOWN:

            pData[0] = 0x02;
            if(ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData) == _TRUE)
            {
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }
            else
            {
                // Failed to Power down
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_TX_QUERY_STREAM_ENCRYPTION_STATUS:

            if(GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED() == 1)
            {
                // Calculate Signature L for Downstream
                ScalerDpTxMstQueryEncryptionWriteShaInput();

                // Caompare Signature L with L' from Downstream
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(ScalerDpTxMstQueryEncryptionCompareShaResult());
            }

            // Check Stream State
            pData[0] = (GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE());

            // Set Stream State
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(pData[0]);

            // Check Stream Encryption
            pData[0] = (GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION() & GET_DP_RX_HDCP_AUTH_ENCRYPTION() & GET_DP_TX_HDCP_ENCRYPTION_ENABLE());

            // Set Stream Encryption
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(pData[0]);

            // Check Stream Authentication
            pData[0] = (GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN() & (GET_DP_RX_HDCP_AUTH_PROC_DONE() & GET_DP_TX_HDCP_AUTH_PROC_PASS()));

            // Set Stream Authentication
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(pData[0]);

            // Check Stream Output Sink Type
            pData[0] = (GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE());

            // Set Stream Output Sink Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(pData[0]);

            // Check Stream Output CP Type
            pData[0] = (GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE() & _HDCP_FEATURE_1_1);

            // Set Stream Output CP Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(pData[0]);

            if(GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED() == 1)
            {
                // Calculate Signature L' for Upstream
                ScalerDpRxMstQueryEncryptionWriteShaInput();

                // Set Stream State Signature L'for Upstream
                for(pData[0] = 0; pData[0] < 20; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], GET_REG_DP_RX_HDCP_SHA_RESULT(pData[0]));
                }
            }
            else
            {
                // Reset Stream State Signature L'
                for(pData[0] = 0; pData[0] < 20; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], 0x00);
                }
            }

            SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();

            break;

        default:

            break;
    }

    SET_DP_TX_DOWN_REPLY_EVENT(_DP_TX_NONE_EVENT);
}

//--------------------------------------------------
// Description  : Dp Tx Write MSG to Downstream Status Check
// Input Value  : MSG Type
// Output Value : True or False
//--------------------------------------------------
bit ScalerDpTxMstWriteMsgToDownstreamStatusCheck(EnumDpMessageType enumMsgType)
{
    // Enable Defer/TimeOut/Nack/Error Retry Machine
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    if(enumMsgType == _DP_DOWN_REQUEST_MSG)
    {
        // Select Write Address
        SET_REG_DP_TX_DOWNSTREAM_TO_DOWN_REQUEST_ADDRESS();
    }
    else if(enumMsgType == _DP_UP_REPLY_MSG)
    {
        // Select Write Address
        SET_REG_DP_TX_DOWNSTREAM_TO_UP_REPLY_ADDRESS();
    }

    // Clear Read Pointer
    CLR_REG_DP_TX_DOWNSTREAM_MSG_BUF();

    // Disable AUX FW Handle Mode
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, 0x00);

    // Reset FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset TX Aux FSM to Aviod HW received 2 times Defer Bug
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT5, _BIT5);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT5, 0x00);

    // Start WR MSG circuit
    SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_DISABLE();
    SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_ENABLE();

    // Polling WR Finished flag set 1 in 20ms
    if(ScalerTimerPollingFlagProc(20, PBD_B6_MSG_WR_FINISH, _BIT0, _TRUE) == _TRUE)
    {
        // Disable Defer/TimeOut/Nack/Error Retry Machine
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_DISABLE();

        // Reset FIFO
        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable AUX FW Handle Mode
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);

        CLR_REG_DP_TX_DOWNSTREAM_MSG_WRITE_FINISH_FLAG();

        return _TRUE;
    }
    else
    {
        // Disable Defer/TimeOut/Nack/Error Retry Machine
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

        SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_DISABLE();

        // Reset FIFO
        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Enable AUX FW Handle Mode
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT5, _BIT5);

        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Modify for Down Request MSG Header
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownRequestHeaderModify(void)
{
    if(((bit)GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST() == _FALSE) && (GET_DP_MSG_REQUEST_ID() != _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS))
    {
        // Modify RAD
        ScalerDpTxMstModifyRAD(_DP_DOWN_REQUEST_MSG);
    }

    // Set LCT
    ScalerSetBit(PBD_B9_MSG_WR_SET0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() << 4));

    pData[0] = (GET_DP_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS) ? GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() : (GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() - 1);

    // Set LCR
    ScalerSetBit(PBD_B9_MSG_WR_SET0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pData[0]);

    // Set Broadcast Bit
    ScalerSetBit(PBD_C1_MSG_WR_SET8, ~_BIT7, GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST());

    // Set Path Bit
    ScalerSetBit(PBD_C1_MSG_WR_SET8, ~_BIT6, GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH());

    // Set TX MSG Write Total Length
    SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(GET_DP_TX_DOWN_REQUEST_BODY_LENGTH());

    // Set MSN Bit
    ScalerSetBit(PBD_C2_MSG_WR_SET9, ~_BIT4, GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Manage for Down Request MSG Body
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstDownRequestMsgAnal(void)
{
    switch(GET_DP_MSG_REQUEST_ID())
    {
        case _DP_MSG_LINK_ADDRESS:

            // Tx Cable Plug
            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                // Analysis Finish
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_ENUM_PATH_RESOURCES:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
                    {
                        if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_RX_REPLY_BUF_FREE();

                            // Analysis Finish
                            SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                    else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
                    {
                        // Report Link Failure
                        SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
                {
                    if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_NO_SUPPORT)
                    {
                        // Analysis Finish
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        if(GET_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE() == _FALSE)
                        {
                            if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                            {
                                if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
                                {
                                    // Analysis Finish
                                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                }
                                else
                                {
                                    if((bit)GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH() == _TRUE)
                                    {
                                        // Sync Downstream Payload ID Table
                                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                    }
                                    else
                                    {
                                        // Analysis Finish
                                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                                    }
                                }
                            }
                            else
                            {
                                if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                                {
                                    // Occupy Reply Pool
                                    CLR_DP_REPLY_POOL_FREE();

                                    // Disable Reply Buffer Free
                                    CLR_DP_RX_REPLY_BUF_FREE();

                                    // Sync Downstream Payload ID Table
                                    SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                                }
                                else
                                {
                                    return _FALSE;
                                }
                            }
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_FAIL)
                {
                    // Reply Error MSG , Nack Reason : Link Failure
                    SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                }
                else
                {
                    return _FALSE;
                }
            }
            else
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                }
                else
                {
                    if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
                    {
                        // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                        SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    }
                    else
                    {
                        if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                        {
                            // Occupy Reply Pool
                            CLR_DP_REPLY_POOL_FREE();

                            // Disable Reply Buffer Free
                            CLR_DP_RX_REPLY_BUF_FREE();

                            // Analysis Finish
                            SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                        }
                        else
                        {
                            return _FALSE;
                        }
                    }
                }
            }

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
                    {
                        // Analysis Finish
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                        SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                    }
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        // Analysis Finish
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(((bit)GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH() == _TRUE) || (GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE))
                {
                    SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_CLEAR_ID_TABLE);
                }
                else
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }

                if(((bit)GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST() == _TRUE) || (GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE))
                {
                    // Set Broadcast Flag
                    SET_DP_TX_DOWN_REQUEST_BROAD_MSG();
                }
            }
            else
            {
                if(GET_DP_RX_SELF_GEN_DOWN_REQUEST_MSG() == _TRUE)
                {
                    CLR_DP_RX_SELF_GEN_DOWN_REQUEST_MSG();

                    // Free DownReq Pool
                    SET_DP_REQUEST_POOL_FREE();
                }
                else
                {
                    // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                    SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
                }
            }


            break;

        case _DP_MSG_POWER_UP_PHY:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Path MSG
                    if((bit)GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH() == _TRUE)
                    {
                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_UP);
                    }
                    else // Node MSG
                    {
                        // Analysis Finish
                        SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                    }
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_UP);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_POWER_DOWN);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_DPCD_READ);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_DPCD_WRITE);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_I2C_READ);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR() > 0)
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
                else
                {
                    if((GET_DP_REPLY_POOL_FREE() == _TRUE) && (GET_DP_RX_REPLY_BUF_FREE() == _TRUE))
                    {
                        // Occupy Reply Pool
                        CLR_DP_REPLY_POOL_FREE();

                        // Disable Reply Buffer Free
                        CLR_DP_RX_REPLY_BUF_FREE();

                        SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_I2C_WRITE);
                    }
                    else
                    {
                        return _FALSE;
                    }
                }
            }
            else
            {
                // Reply Error MSG , Nack Reason : _BAD_PARAM Failure
                SET_DP_TX_ILLEGAL_DOWN_REQUEST_MSG();
            }

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                if((GET_DP_TX_HDCP_AUTH_PROC_PASS() == _FALSE) && (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE))
                {
                    SET_DP_TX_HDCP_AUTH_START();

                    SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_QUERY_STREAM_ENCRYPTION_STATUS);
                }
                else
                {
                    // Analysis Finish
                    SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
                }
            }
            else
            {
                // Analysis Finish
                SET_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();
            }

            break;

        default:
            break;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Steering Stream to Stream SourceX
// Input Value  : Stream Number
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstSyncDownStreamTableSetting(BYTE ucPayloadID, BYTE ucStartPosition, BYTE ucLength)
{
    // Clear Table Update and ACT Bit
    pData[0] = 0x01;

    if(ScalerDpTxAuxNativeWrite(0x00, 0x02, 0xC0, 1, pData) == _FALSE)
    {
        return _FALSE;
    }

    // Update Payload ID Table
    pData[0] = ucPayloadID;
    pData[1] = ucStartPosition;
    pData[2] = ucLength;

    if(ScalerDpTxAuxNativeWrite(0x00, 0x01, 0xC0, 3, pData) == _FALSE)
    {
        return _FALSE;
    }

    for(pData[1] = 0; pData[1] < 20; pData[1]++)
    {
        // Wait Rx Table Update
        ScalerTimerDelayXms(5);

        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC0, 1, pData) == _TRUE)
        {
            if((pData[0] & _BIT0) == _BIT0)
            {
                if((ucPayloadID == 0x00) && (ucStartPosition == 0x00) && (ucLength == 0x3F))
                {
                    return _TRUE;
                }

                // Clear ACT Transmitted Flag
                CLR_REG_DP_RX_SEND_ACT_FLAG();

                // Transmit ACT
                SET_REG_DP_RX_SEND_ACT_ENABLE();

                for(pData[1] = 0; pData[1] < 20; pData[1]++)
                {
                    ScalerTimerDelayXms(2);

                    // Check ACT Transmitted
                    if(GET_REG_DP_RX_SEND_ACT_FLAG() == _TRUE)
                    {
                        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC0, 1, pData) == _TRUE)
                        {
                            if((pData[0] & _BIT1) == 0x00)
                            {
                                // Clear ACT Transmitted Flag
                                CLR_REG_DP_RX_SEND_ACT_FLAG();

                                // Retry Transmit ACT
                                SET_REG_DP_RX_SEND_ACT_ENABLE();
                            }
                            else
                            {
                                pData[0] = _BIT0;

                                // Clear Update Table and ACT Bit
                                ScalerDpTxAuxNativeWrite(0x00, 0x02, 0xC0, 1, pData);

                                return _TRUE;
                            }
                        }
                    }
                }

                break;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Rx MSG Reply for DP
// Input Value  : Reply Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyDirectlyMsg(void)
{
    BYTE pucData[2];

    memset(pucData, 0, sizeof(pucData));

    switch(GET_DP_MSG_REQUEST_ID())
    {
        case _DP_MSG_ENUM_PATH_RESOURCES:

            // Set Message Body Length = 6
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(6);

            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_REQUEST_ID(_DP_MSG_ENUM_PATH_RESOURCES);

            // Set Port Num
            SET_DP_DOWN_REPLY_ENUM_PATH_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_ENUM_PATH_MSG_PORT_NUM());

            if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
            {
                // Set Full PBN
                SET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN((_DP_TOTAL_TIME_SLOT_NUM - 1) * GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM()));

                SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(ScalerDpTxMstGetAvailablePBN());
            }
            else
            {
                // Set Full PBN
                SET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN(_DP_TOTAL_TIME_SLOT_NUM  * GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM()));

                if(ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2) == 0)
                {
                    SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(GET_DP_DOWN_REPLY_ENUM_PATH_MSG_FULL_PBN());
                }
                else
                {
                    SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(0);
                }
            }

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            // Set Message Body Length = 5
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(5);

            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_ALLOCATE_PAYLOAD);

            // Set Port Number
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PORT_NUM());

            // Set Payload ID
            SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID());

            if(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() > 0)
            {
                // Get # of Allocate Timeslot
                PDATA_WORD(0) = (GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() / GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM())) +
                                (((GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN() % GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM())) > 0) ? 1 : 0);

                // Calculate Allocated PBN
                PDATA_WORD(0) = PDATA_WORD(0) * GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM());

                // Set Allocated PBN
                SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(PDATA_WORD(0));
            }
            else
            {
                // Set PBN
                SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(GET_DP_DOWN_REQUEST_ALLOCATE_PAYLOAD_MSG_PBN());
            }

            break;

        case _DP_MSG_QUERY_PAYLOAD:

            // Set Message Body Length = 4
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(4);

            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_REQUEST_ID(_DP_MSG_QUERY_PAYLOAD);

            // Set Port Number
            SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PORT_NUM());

            for(pucData[0] = _DP_ST_SOURCE3; pucData[0] <= _DP_ST_SOURCE5; pucData[0]++)
            {
                if(g_pucDpStreamToIdMapping[ScalerDpRxMstStreamMuxCheck(pucData[0]) - 1] == GET_DP_DOWN_REQUEST_QUERY_PAYLOAD_MSG_PAYLOAD_ID())
                {
                    if(ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(pucData[0]), 0x3F) != 0)
                    {
                        // Calculate # of Allocated Timeslot
                        pucData[1] = ScalerGetBit(GET_DP_TX_STX_END_ADDRESS(pucData[0]), 0x3F) -
                                     ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(pucData[0]), 0x3F) + 1;

                        // Calculate Allocated PBN
                        PDATA_WORD(1) = GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM()) * (WORD)pucData[1];

                        // Set Allocated PBN
                        SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(PDATA_WORD(1));
                    }
                    else
                    {
                        // Set Allocated PBN
                        SET_DP_DOWN_REPLY_QUERY_PAYLOAD_MSG_ALLOCATED_PBN(0);
                    }
                }
            }

            break;

        case _DP_MSG_CLEAR_PAYLOAD_ID_TABLE:

            // Set Message Body Length = 1
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(1);

            // Set Reply Type
            SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_CLEAR_ID_TABLE_MSG_REQUEST_ID(_DP_MSG_CLEAR_PAYLOAD_ID_TABLE);

            break;

        case _DP_MSG_POWER_UP_PHY:

            // Set Message Body Length = 2
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_DOWN_REPLY_POWER_UP_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_POWER_UP_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_POWER_UP_MSG_REQUEST_ID(_DP_MSG_POWER_UP_PHY);

            // Set Port Number
            SET_DP_DOWN_REPLY_POWER_UP_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_POWER_UP_MSG_PORT_NUM());

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            // Set Message Body Length = 2
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_REQ_ID(_DP_MSG_POWER_DOWN_PHY);

            // Set Port Number
            SET_DP_DOWN_REPLY_POWER_DOWN_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_POWER_DOWN_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_DPCD_READ:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH((3 + GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ()));

            SET_DP_DOWN_REPLY_MSG_REMOTE_DPCD_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_READ);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_PORT_NUM());

            // Set Number Of Read Byte
            SET_DP_DOWN_REPLY_REMOTE_DPCD_READ_MSG_NUM_OF_READ(GET_DP_DOWN_REQUEST_REMOTE_DPCD_READ_MSG_NUM_OF_READ());

            break;

        case _DP_MSG_REMOTE_DPCD_WRITE:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_DOWN_REPLY_REMOTE_DPCE_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_DPCD_WRITE);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_DPCD_WRITE_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_DPCD_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_READ:

            if(g_unDpRequestPool.stRemoteI2CRead.b2NumOfI2CWriteTran == 0)
            {
                // Set Message Body Length
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(3 + g_unDpRequestPool.pucData[3]);

                // Set Number Of Byte Read
                SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(g_unDpRequestPool.pucData[3]);
            }
            else if(g_unDpRequestPool.stRemoteI2CRead.b2NumOfI2CWriteTran == 1)
            {
                // Set Message Body Length
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(3 + g_unDpRequestPool.pucData[7]);

                // Set Number Of Byte Read
                SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(g_unDpRequestPool.pucData[7]);
            }
            else if(g_unDpRequestPool.stRemoteI2CRead.b2NumOfI2CWriteTran == 2)
            {
                // Set Message Body Length
                SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(3 + g_unDpRequestPool.pucData[11]);

                // Set Number Of Byte Read
                SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_NUM_OF_READ(g_unDpRequestPool.pucData[11]);
            }

            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_READ);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_I2C_READ_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_PORT_NUM());

            break;

        case _DP_MSG_REMOTE_I2C_WRITE:

            // Set Message Body Length
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(2);

            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_REQUEST_ID(_DP_MSG_REMOTE_I2C_WRITE);

            // Set Port Number
            SET_DP_DOWN_REPLY_REMOTE_I2C_WRITE_MSG_PORT_NUM(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_PORT_NUM());

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            // Set Message Body Length = 24
            SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(24);

            // Set Reserve Bit to 0
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_ZEROS();

            // Set Reply Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REPLY_TYPE(_DP_MSG_ACK);

            // Set Request ID
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_REQUEST_ID(_DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS);

            // Get Downstream Port Power Status
            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                ScalerDpTxAuxNativeRead(0x00, 0x06, 0x00, 1, pData);

                pData[1] = ((pData[0] & 0x07) == _BIT0) ? _DP_STREAM_ACTIVE : _DP_STREAM_NOT_ACTIVE;
            }
            else
            {
                pData[1] = _DP_STREAM_NOT_EXIST;
            }

            // Set Stream State
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_STATE(pData[1]);

            // Set Stream Repeater Function Present
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_REPEATER_PRESENT(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER());

            // Set Stream Encryption
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ENCRYPTION(GET_DP_TX_HDCP_ENCRYPTION_ENABLE());

            // Set Stream Authentication
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_AUTHEN(GET_DP_TX_HDCP_AUTH_PROC_PASS());

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                pData[0] = (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) ? _DP_OUTPUT_SINK_TYPE_MSG_NO_SUPPORT : _DP_OUTPUT_SINK_TYPE_NON_AUTHENTICABLE;
            }
            else
            {
                pData[0] = 0x00;
            }

            // Set Stream Output Sink Type
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_SINK_TYPE(pData[0]);

            pData[0] = (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE) ? _HDCP_FEATURE_1_1 : 0x00;

            // Set Stream Output CP Type => HDCP 1.x
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_OUTPUT_CP_TYPE(pData[0]);

            if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE))
            {
                // Set Signed
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(1);

                // Calculate Signature L' for Upstream
                ScalerDpRxMstQueryEncryptionWriteShaInput();

                // Set Stream State Signature L'for Upstream
                for(pData[0] = 0; pData[0] < 20; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], GET_REG_DP_RX_HDCP_SHA_RESULT(pData[0]));
                }
            }
            else
            {
                // Set Signed
                SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_SIGNED(0);

                // Reset Stream State Signature L'
                for(pData[0] = 0; pData[0] < 20; pData[0]++)
                {
                    SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(pData[0], 0x00);
                }
            }

            // Set Stream ID
            SET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID(GET_DP_DOWN_REQUEST_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());

            break;

        default:

            break;
    }

    if((GET_DP_MSG_REQUEST_ID() == _DP_MSG_CLEAR_PAYLOAD_ID_TABLE) || (GET_DP_MSG_REQUEST_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS))
    {
        // Set LCT
        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(0x10);

        // Set LCR
        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(0x00);
    }
    else
    {
        // Set LCT
        SET_REG_DP_RX_UPSTREAM_REPLY_LCT(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() << 4);

        // Set LCR
        SET_REG_DP_RX_UPSTREAM_REPLY_LCR(GET_REG_DP_RX_DOWN_REQUEST_MSG_LCT() - 1);

        // Set RAD
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD0(GET_REG_DP_RX_DOWN_REQUEST_RAD0());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD1(GET_REG_DP_RX_DOWN_REQUEST_RAD1());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD2(GET_REG_DP_RX_DOWN_REQUEST_RAD2());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD3(GET_REG_DP_RX_DOWN_REQUEST_RAD3());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD4(GET_REG_DP_RX_DOWN_REQUEST_RAD4());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD5(GET_REG_DP_RX_DOWN_REQUEST_RAD5());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD6(GET_REG_DP_RX_DOWN_REQUEST_RAD6());
        SET_REG_DP_RX_UPSTREAM_REPLY_RAD7(GET_REG_DP_RX_DOWN_REQUEST_RAD7());
    }

    // Set Broadcast and Path
    SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(GET_REG_DP_RX_DOWN_REQUEST_MSG_BROADCAST());
    SET_REG_DP_RX_UPSTREAM_REPLY_PATH(GET_REG_DP_RX_DOWN_REQUEST_MSG_PATH());

    // Set MSN
    SET_REG_DP_RX_UPSTREAM_REPLY_MSN(GET_REG_DP_RX_DOWN_REQUEST_MSG_MSN());
}

//--------------------------------------------------
// Description  : Get Tx CRC Status of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstGetDownReplyCrcFailed(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return GET_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
    }
    else
    {
        return GET_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
    }
}

//--------------------------------------------------
// Description  : Get Tx LCT of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpTxMstGetDownReplyLct(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return (((BYTE)g_stTxMsgBackupHeaderInfo0.b4MsgLct) << 4);
    }
    else
    {
        return (((BYTE)g_stTxMsgBackupHeaderInfo1.b4MsgLct) << 4);
    }
}

//--------------------------------------------------
// Description  : Get Tx LCR of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpTxMstGetDownReplyLcr(void)
{
    if(GET_DP_MSG_REPLY_ID() == _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
    {
        if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
        {
            return (((BYTE)g_stTxMsgBackupHeaderInfo0.b4MsgLcr) & 0x0f);
        }
        else
        {
            return (((BYTE)g_stTxMsgBackupHeaderInfo1.b4MsgLcr) & 0x0f);
        }
    }
    else
    {
        if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
        {
            return ((((BYTE)g_stTxMsgBackupHeaderInfo0.b4MsgLcr) & 0x0f) - 1);
        }
        else
        {
            return ((((BYTE)g_stTxMsgBackupHeaderInfo1.b4MsgLcr) & 0x0f) - 1);
        }
    }
}

//--------------------------------------------------
// Description  : Get Tx Broadcast Bit of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstGetDownReplyBroadcastBit(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stTxMsgBackupHeaderInfo0.b1MsgBroadcast;
    }
    else
    {
        return g_stTxMsgBackupHeaderInfo1.b1MsgBroadcast;
    }
}

//--------------------------------------------------
// Description  : Get Tx Path Bit of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstGetDownReplyPathBit(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stTxMsgBackupHeaderInfo0.b1MsgPath;
    }
    else
    {
        return g_stTxMsgBackupHeaderInfo1.b1MsgPath;
    }
}

//--------------------------------------------------
// Description  : Get Tx MSN of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstGetDownReplyMsn(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return g_stTxMsgBackupHeaderInfo0.b1MsgMsn;
    }
    else
    {
        return g_stTxMsgBackupHeaderInfo1.b1MsgMsn;
    }
}

//--------------------------------------------------
// Description  : Get Tx Length of Bypass MSG for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpTxMstGetDownReplyLength(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        return GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    }
    else
    {
        return GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    }
}

//--------------------------------------------------
// Description  : Tx Bypass MSG Header Modify for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyBypassHeaderModify(void)
{
    // Set LCT
    SET_REG_DP_RX_UPSTREAM_REPLY_LCT(ScalerDpTxMstGetDownReplyLct());

    // Set LCR
    SET_REG_DP_RX_UPSTREAM_REPLY_LCR(ScalerDpTxMstGetDownReplyLcr());

    // Update RAD
    ScalerDpTxMstModifyRAD(_DP_DOWN_REPLY_MSG);

    // Set Broadcast
    SET_REG_DP_RX_UPSTREAM_REPLY_BROADCAST(ScalerDpTxMstGetDownReplyBroadcastBit());

    // Set Path
    SET_REG_DP_RX_UPSTREAM_REPLY_PATH(ScalerDpTxMstGetDownReplyPathBit());

    // Set MSN
    SET_REG_DP_RX_UPSTREAM_REPLY_MSN(ScalerDpTxMstGetDownReplyMsn());

    // Set MSG Body Length
    SET_REG_DP_RX_UPSTREAM_REPLY_LENGTH(ScalerDpTxMstGetDownReplyLength());
}

//--------------------------------------------------
// Description  : Tx DownReply MSG Analysis for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstDownReplyBypass(void)
{
    BYTE pucData[2];

    memset(pucData, 0, sizeof(pucData));

    switch(GET_DP_MSG_REPLY_ID())
    {
        case _DP_MSG_ENUM_PATH_RESOURCES:

            if(ScalerDpTxMstGetDownReplyPathBit() == _TRUE)
            {
                // Get DownStream Available PBN
                PDATA_WORD(0) = ScalerDpTxMstGetAvailablePBN();

                if(PDATA_WORD(0) < GET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN())
                {
                    // Set Available PBN
                    SET_DP_DOWN_REPLY_ENUM_PATH_MSG_AVAILABLE_PBN(PDATA_WORD(0));
                }
            }

            SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();

            break;

        case _DP_MSG_ALLOCATE_PAYLOAD:

            if(GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN() == 0)
            {
                if(ScalerDpTxMstGetDownReplyPathBit() == _TRUE)
                {
                    SET_DP_TX_DOWN_REPLY_EVENT(_DP_TX_SYNC_PAYLOAD_TABLE);
                }
                else
                {
                    SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
                }
            }
            else
            {
                // Get Using STX for this ID
                pucData[0] = ScalerDpRxMstSearchMatchStream(GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PAYLOAD_ID()) + 1;

                for(pucData[1] = _DP_ST_SOURCE3; pucData[1] <= _DP_ST_SOURCE5; pucData[1]++)
                {
                    if(ScalerDpRxMstStreamMuxCheck(pucData[1]) == pucData[0])
                    {
                        pucData[0] = (ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(pucData[1])) & 0x3F) -
                                     (ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(pucData[1])) & 0x3F) + 1;

                        break;
                    }
                }

                if((pucData[0] >= 1) && (pucData[0] <= 63))
                {
                    PDATA_WORD(1) = (WORD)GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM()) * (WORD)pucData[0];

                    if(PDATA_WORD(1) > GET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN())
                    {
                        SET_DP_DOWN_REPLY_ALLOCATE_PAYLOAD_MSG_PBN(PDATA_WORD(1));
                    }
                }

                // For PBN > 0 Case
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_MSG_POWER_DOWN_PHY:

            if(ScalerDpTxMstGetDownReplyPathBit() == _TRUE)
            {
                SET_DP_TX_DOWN_REPLY_EVENT(_DP_TX_POWER_DOWN);
            }
            else
            {
                SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();
            }

            break;

        case _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS:

            SET_DP_TX_DOWN_REPLY_EVENT(_DP_TX_QUERY_STREAM_ENCRYPTION_STATUS);

            break;

        default:

            SET_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();

            break;
    }
}

//--------------------------------------------------
// Description  : Tx Sync Payload ID Table for DP
// Input Value  : Virtual ID and PBN
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstSyncTableProcess(BYTE ucPayloadID, WORD usPBN)
{
    EnumDpStreamSourceNum enumTxCurrentSTX = _DP_ST_SOURCE3;
    BYTE ucTxTargeTimeSlotLength = 0;
    BYTE ucTxTargetStartPosition = 0;
    BYTE ucTxTargetEndPosition = 0;
    SBYTE chTxTimeSlotOffset = 0;

    pData[0] = ScalerDpRxMstSearchMatchStream(ucPayloadID) + 1;

    // Find which ST Source Is assigned to the STx Containing current payload ID
    if(pData[0] == GET_REG_DP_RX_MST_ST3_SOURCE_STATUS())
    {
        enumTxCurrentSTX = _DP_ST_SOURCE3;
    }
    else if(pData[0] == GET_REG_DP_RX_MST_ST4_SOURCE_STATUS())
    {
        enumTxCurrentSTX = _DP_ST_SOURCE4;
    }
    else if(pData[0] == GET_REG_DP_RX_MST_ST5_SOURCE_STATUS())
    {
        enumTxCurrentSTX = _DP_ST_SOURCE5;
    }
    else
    {
        DebugMessageDigital("ucTxCurrentSTX Error", 0);

        // Failed to allocate VC
        return _FALSE;
    }

    // Calculate Required Timeslots Number to allocate
    ucTxTargeTimeSlotLength = (usPBN / GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM())) +
                              (((usPBN % GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM())) > 0) ? 1 : 0);

    // Add Payload Load ID if Current Timeslot Start is not assigned yet
    if((ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(enumTxCurrentSTX)) & 0x3F) != 0)
    {
        // Set Start Position
        ucTxTargetStartPosition = (ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(enumTxCurrentSTX)) & 0x3F);
        ucTxTargetEndPosition = (ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(enumTxCurrentSTX)) & 0x3F);

        // Increasing or Decreasing Timeslots
        if(ucTxTargeTimeSlotLength != 0)
        {
            // Calculate Timeslot Offset between with New Allocate and Original Allocate
            chTxTimeSlotOffset = (SBYTE)ucTxTargeTimeSlotLength - (SBYTE)(ucTxTargetEndPosition - ucTxTargetStartPosition + 1);

            // Modify Timeslot End Position
            ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(enumTxCurrentSTX)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucTxTargetEndPosition + chTxTimeSlotOffset) & 0x3F));
        }
        else // Delete
        {
            chTxTimeSlotOffset = -(SBYTE)(ucTxTargetEndPosition - ucTxTargetStartPosition + 1);

            // Delete Allocate Timeslot
            ScalerSetBit((GET_DP_TX_STX_START_ADDRESS(enumTxCurrentSTX)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(enumTxCurrentSTX)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        }

        // Based On Offset to Modify Timeslot Allocated
        for(pData[0] = _DP_ST_SOURCE3; pData[0] <= _DP_ST_SOURCE5; pData[0]++)
        {
            if(enumTxCurrentSTX != pData[0])
            {
                if((ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(pData[0])) & 0x3F) > ucTxTargetStartPosition)
                {
                    // Modify Start Position
                    ScalerSetByte(GET_DP_TX_STX_START_ADDRESS(pData[0]), ((ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(pData[0])) + chTxTimeSlotOffset) & 0x3F));

                    // Modify End Position
                    ScalerSetByte(GET_DP_TX_STX_END_ADDRESS(pData[0]), ((ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(pData[0])) + chTxTimeSlotOffset) & 0x3F));
                }
            }
        }
    }
    else if(usPBN != 0)
    {
        // Find TimeSlot Start Position = Current Max End Position + 1
        for(pData[0] = _DP_ST_SOURCE3; pData[0] <= _DP_ST_SOURCE5; pData[0]++)
        {
            if(enumTxCurrentSTX != pData[0])
            {
                if(ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(pData[0])) >= ucTxTargetStartPosition)
                {
                    ucTxTargetStartPosition = ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(pData[0])) + 1;
                }
            }
        }

        // Set Daisy Chain Start TimeSlot Position
        ScalerSetBit((GET_DP_TX_STX_START_ADDRESS(enumTxCurrentSTX)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucTxTargetStartPosition & 0x3F));

        // Set Daisy Chain End TimeSlot Position
        ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(enumTxCurrentSTX)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucTxTargetStartPosition + ucTxTargeTimeSlotLength - 1) & 0x3F));

        // Set Start Position
        ucTxTargetStartPosition = (ScalerGetByte(GET_DP_TX_STX_START_ADDRESS(enumTxCurrentSTX)) & 0x3F);
        ucTxTargetEndPosition = (ScalerGetByte(GET_DP_TX_STX_END_ADDRESS(enumTxCurrentSTX)) & 0x3F);
    }

    if(usPBN == 0)
    {
        // Clear STX_Source Mux
        if(enumTxCurrentSTX == _DP_ST_SOURCE3)
        {
            SET_REG_DP_RX_MST_ST3_SOURCE_STATUS(0x00);
        }
        else if(enumTxCurrentSTX == _DP_ST_SOURCE4)
        {
            SET_REG_DP_RX_MST_ST4_SOURCE_STATUS(0x00);
        }
        else if(enumTxCurrentSTX == _DP_ST_SOURCE5)
        {
            SET_REG_DP_RX_MST_ST5_SOURCE_STATUS(0x00);
        }
    }

    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        // Use 0x1C0~0x1C2 to Sync Table and Issuing ACT => Include Retry Once
        if((ScalerDpTxMstSyncDownStreamTableSetting(ucPayloadID, ucTxTargetStartPosition, ucTxTargeTimeSlotLength) == _TRUE) ||
           (ScalerDpTxMstSyncDownStreamTableSetting(ucPayloadID, ucTxTargetStartPosition, ucTxTargeTimeSlotLength) == _TRUE))
        {
            return _TRUE;
        }
        else
        {
            // Failed to allocate VC
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

/*
//--------------------------------------------------
// Description  : Monitor Tx Down stream Bandwidth
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMonitorDownstreamBW(void)
{
    BYTE ucCurrentPBNPerTimerslot = GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM());

    if(GET_DP_TX_LINK_PBN_PER_TIMESOLT() == 0)
    {
        // Set PBN per Timeslot
        SET_DP_TX_LINK_PBN_PER_TIMESOLT(ucCurrentPBNPerTimerslot);
    }

    // Check Tx Downstream BW Whether Change or not
    if((GET_DP_TX_LINK_PBN_PER_TIMESOLT() != ucCurrentPBNPerTimerslot))
    {
        if(GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT)
        {
            if((GET_REG_DP_RX_DAIZY_ST3_START() != 0) || (GET_REG_DP_RX_DAIZY_ST4_START() != 0) || (GET_REG_DP_RX_DAIZY_ST5_START() != 0))
            {
                if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0xC0, 1, pData) == _TRUE)
                {
                    // VC Payload Table Exception Clear
                    if((pData[0] & _BIT2) != _BIT2)
                    {
                        // Timeslot Local Recovery
                        ScalerDpTxLocalRecoveryPayloadTable(ucCurrentPBNPerTimerslot);
                    }
                }
            }
        }
        else
        {
            // Get STx
            pData[0] = ScalerDpRxMstStreamMuxCheck(_DP_ST_SOURCE2);

            // Get STx using Length : End Position - Start Position + 1
            pData[1] = GET_DP_RX_MST_STREAM_TIME_SLOT(pData[0] - 1);

            if(((WORD)ucCurrentPBNPerTimerslot << 6) < ((WORD)pData[1] * GET_DP_TX_LINK_PBN_PER_TIMESOLT()))
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

                SET_DP_RX_MST2SST_ENABLE(_DISABLE);
            }
        }

#if(_DP_SUPPORT == _ON)
        // if Up Request Support
        if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == _BIT1)
        {
            // Issue Resource Status Notify
            SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);
        }
#endif

        // Set PBN per Timeslot
        SET_DP_TX_LINK_PBN_PER_TIMESOLT(ucCurrentPBNPerTimerslot);
    }

    if(GET_DP_RX_SELF_GEN_UP_REQUEST_RETRY() == _DP_MSG_RESOURCE_STATUS_NOTIFY)
    {
        CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

        SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_RESOURCE_STATUS_NOTIFY);
    }
}

//--------------------------------------------------
// Description  : Tx Payload Table Local Recovery as Link Loss
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxLocalRecoveryPayloadTable(BYTE ucCurrentPBNPerTimerslot)
{
    WORD usCurrentAvailablePBN = ucCurrentPBNPerTimerslot * 63;
    WORD usPastAllocatedPBN = 0;
    BYTE ucStreamOrder[3];

    // Initial Stream Order
    ucStreamOrder[0] = 0;
    ucStreamOrder[1] = 1;
    ucStreamOrder[2] = 2;

    // Sorting Bypass Stream based on Start Position
    pData[0] = GET_REG_DP_RX_DAIZY_ST3_START();
    pData[1] = GET_REG_DP_RX_DAIZY_ST4_START();
    pData[2] = GET_REG_DP_RX_DAIZY_ST5_START();

    if(pData[0] > pData[1])
    {
        ucStreamOrder[0] = 1;
        ucStreamOrder[1] = 0;
    }

    if(pData[2] < pData[ucStreamOrder[0]])
    {
        ucStreamOrder[2] = ucStreamOrder[1];
        ucStreamOrder[1] = ucStreamOrder[0];
        ucStreamOrder[0] = 2;
    }
    else if(pData[2] < pData[ucStreamOrder[1]])
    {
        ucStreamOrder[2] = ucStreamOrder[1];
        ucStreamOrder[1] = 2;
    }
    else
    {
        ucStreamOrder[2] = 2;
    }

    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        if(ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) != 0)
        {
            // Get Past Allocated PBN
            usPastAllocatedPBN = (ScalerGetBit(GET_DP_TX_STX_START_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) -
                                  ScalerGetBit(GET_DP_TX_STX_END_ADDRESS(ucStreamOrder[pData[0]] + 2), 0x3F) + 1) *
                                  GET_DP_TX_LINK_PBN_PER_TIMESOLT();

            // Get STx
            pData[1] = ScalerDpRxMstStreamMuxCheck(ucStreamOrder[pData[0]] + 2) - 1;

            if(usCurrentAvailablePBN >= usPastAllocatedPBN)
            {
                // Get Remain Available PBN
                usCurrentAvailablePBN = usCurrentAvailablePBN - usPastAllocatedPBN;

                // Modify Daisy Chain Timeslot Length
                ScalerDpTxMstSyncTableProcess(g_pucDpStreamToIdMapping[pData[1]], usPastAllocatedPBN);
            }
            else
            {
                // Delete Daisy Chain Timeslot
                ScalerDpTxMstSyncTableProcess(g_pucDpStreamToIdMapping[pData[1]], 0);
            }
        }
    }
}
*/

//--------------------------------------------------
// Description  : Calculate Current Available PBN
// Input Value  : None
// Output Value : Available PBN
//--------------------------------------------------
WORD ScalerDpTxMstGetAvailablePBN(void)
{
    // Calculate Remain PBN
    pData[1] = 0;

    // Get Num of Allocated Timeslots
    for(pData[0] = 0; pData[0] < 3; pData[0]++)
    {
        if(pData[1] < (ScalerGetBit((GET_DP_TX_STX_END_ADDRESS(pData[0] + 2)), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) & 0x3F))
        {
            pData[1] = (ScalerGetBit((GET_DP_TX_STX_END_ADDRESS(pData[0] + 2)), (_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) & 0x3F);
        }
    }

    // Get DownStream Available PBN
    return (WORD)((_DP_TOTAL_TIME_SLOT_NUM - 1 - pData[1]) * GET_DP_PBN_PER_TIME_SLOT(GET_DP_TX_DOWNSTREAM_LINK_RATE(), GET_DP_TX_DOWNSTREAM_LANE_NUM()));
}

//--------------------------------------------------
// Description  : Modify RAD
// Input Value  : Target Message Type
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstModifyRAD(EnumDpMessageType enumMsgType)
{
    if(GET_DP_MSG_REPLY_ID() != _DP_MSG_QUERY_STREAM_ENCRYPTION_STATUS)
    {
        if(enumMsgType == _DP_DOWN_REQUEST_MSG)
        {
            PDATA_WORD(1) = RET_REG_ADDR_DP_RX_UPSTREAM_DOWN_RAD0_RAD1();
            PDATA_WORD(2) = PBD_BA_MSG_WR_SET1;
            pData[1] = GET_REG_DP_RX_DOWN_REQUEST_MSG_LCR();

            // Record Input Port
            pData[15] = _DP_PORT0;
        }
        else // For enumMsgType == _DP_DOWN_REPLY_MSG and other MSG type default setting
        {
            // Update RAD
            PDATA_WORD(1) = PBD_D0_MSG_RD_DATA1;
            PDATA_WORD(2) = RET_REG_ADDR_DP_RX_UPSTREAM_REPLY_RAD0_RAD1();
            pData[1] = ((GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) ? g_stTxMsgBackupHeaderInfo0.b4MsgLcr : g_stTxMsgBackupHeaderInfo1.b4MsgLcr);

            // Record Output Port
            pData[15] = _DP_PORT1;
        }

        for(pData[0] = 0; pData[0] < 7; pData[0]++)
        {
            ScalerSetByte((PDATA_WORD(2) + pData[0]),
                          ((enumMsgType == _DP_DOWN_REQUEST_MSG) ? ScalerGetByte(PDATA_WORD(1) + pData[0]) :
                           ((GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE) ? g_stTxMsgBackupHeaderInfo0.pucMsgRad[pData[0]] : g_stTxMsgBackupHeaderInfo1.pucMsgRad[pData[0]])));
        }

        if(pData[1] != 0)
        {
            for(pData[0] = 0; pData[0] < pData[1] - 1; pData[0]++)
            {
                if(pData[0] % 2 == 0)
                {
                    SET_REG_DP_RX_REPLY_RAD_MSB(PDATA_WORD(2), GET_REG_DP_RX_BYPASS_RAD_LSB(PDATA_WORD(2)));
                }
                else
                {
                    SET_REG_DP_RX_REPLY_RAD_LSB(PDATA_WORD(2), GET_REG_DP_RX_BYPASS_RAD_MSB(PDATA_WORD(2) + 1));

                    PDATA_WORD(2) = PDATA_WORD(2) + 1;
                }
            }
        }
        else
        {
            pData[0] = 0;
        }

        if(pData[0] % 2 == 0)
        {
            ScalerSetBit(PDATA_WORD(2), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (pData[15] << 4));
        }
        else
        {
            ScalerSetBit(PDATA_WORD(2), ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pData[15]);
        }
    }
}

//--------------------------------------------------
// Description  : Tx Error MSG Reply for DP
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstIllegalMsgReply(void)
{
    SET_DP_TX_UP_REPLY_BODY_LENGTH(19);

    //================ Body Info ==============

    // Set Reply Type
    SET_DP_REPLY_ILLEGAL_MSG_REPLY_TYPE(_DP_MSG_NACK);

    // Set Request ID
    SET_DP_REPLY_ILLEGAL_MSG_REQUESET_ID(GET_DP_TX_UP_REQUEST_BACKUP_DATA(_UP_REQ_BACK_UP_MSG_ID));

#if(_DP_SUPPORT == _ON)
    // Set GUID
    for(pData[0] = 0; pData[0] < 16; pData[0]++)
    {
        SET_DP_REPLY_ILLEGAL_MSG_GUID(pData[0], GET_REG_DP_DPCD_INFO(0x00, 0x00, (0x30 + pData[0])));
    }
#endif

    // Set NACK Reason
    SET_DP_REPLY_ILLEGAL_MSG_NACK_REASON(_CRC_FAILURE);

    SET_DP_REPLY_ILLEGAL_MSG_NACK_DATA(0);

    //================ Header Info ==============
    // Set LCT
    SET_REG_DP_TX_DOWNSTREAM_MSG_LCT(1);

    // Set LCR
    SET_REG_DP_TX_DOWNSTREAM_MSG_LCR(0);

    // Set Broadcast Bit
    SET_REG_DP_TX_DOWNSTREAM_MSG_BROADCAST(GET_REG_DP_TX_UPSTREAM_MSG_BROADCAST());

    // Set Path Bit
    SET_REG_DP_TX_DOWNSTREAM_MSG_PATH(GET_REG_DP_TX_UPSTREAM_MSG_PATH());

    // Set TX MSG Write Total Length
    SET_REG_DP_TX_DOWNSTREAM_MSG_LENGTH(GET_DP_TX_UP_REPLY_BODY_LENGTH());

    // Set MSG Bit
    SET_REG_DP_TX_DOWNSTREAM_MSG_MSN(GET_REG_DP_TX_UPSTREAM_MSG_MSN());

    /*
    if(GET_DP_RX_MSG_ERROR_TYPE() != _NONE_MSG_ERROR)
    {
        switch(GET_DP_RX_MSG_ERROR_TYPE())
        {
            case _WRITE_FAILURE:

                break;

            case _INVALID_RAD:

                break;

            case _CRC_FAILURE:

                break;

            case _BAD_PARAM:

                break;

            case _DEFER:

                break;

            case _LINK_FAILURE:

                break;

            case _NO_RESOURCES:

                break;

            case _DPCD_FAIL:

                break;

            case _I2C_NAK:

                break;

            case _ALLOCATE_FAIL:

                break;

            default:

                break;
        }

        //SET_DP_RX_EVENT(_NONE_MSG_ERROR);
    }
    */
}

//--------------------------------------------------
// Description  : Tx I2C Over Aux Read Down Stream
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDpTxMstI2CRead(void)
{
    BYTE ucArrayIndex = 2;
    BYTE ucLength = _DP_I2C_MAX_TRANSACTION_LENGTH;
    BYTE ucReadIndex = 0;
    BYTE pucData[3];
    BYTE ucCnt = 0;
    bit bMot = 1;

    memset(pucData, 0, sizeof(pucData));

    if(GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE() > 0)
    {
        for(ucCnt = 0; ucCnt < GET_DP_DOWN_REQUEST_REMOTE_I2C_READ_MSG_NUM_OF_WRITE(); ucCnt++)
        {
            // Get write Length Offset
            pucData[0] = ucArrayIndex + 1;

            // Get write Data Offset
            pucData[1] = pucData[0] + 1;

            // Get MOT and Transaction Delay Offset
            pucData[2] = pucData[1] + g_unDpRequestPool.pucData[pucData[0]];

            // Set I2C Write Command
            if(ScalerDpTxAuxI2CoverWrite(g_unDpRequestPool.pucData[ucArrayIndex], g_unDpRequestPool.pucData[pucData[0]], &g_unDpRequestPool.pucData[pucData[1]],
                                         (bit)(g_unDpRequestPool.pucData[pucData[2]] & _BIT4)) == _TRUE)
            {
                // Set I2C Transaction Delay
                ScalerTimerDelayXms((g_unDpRequestPool.pucData[pucData[2]] & 0x0F) * 10);

                // Set Offset to Indicate Write_I2C_Device ID for Next Write Transcation
                ucArrayIndex = pucData[2] + 1;
            }
            else
            {
                // I2C Write Fail
                return _FALSE;
            }
        }
    }

    do
    {
        if((g_unDpRequestPool.pucData[ucArrayIndex + 1] - ucReadIndex) <= _DP_I2C_MAX_TRANSACTION_LENGTH)
        {
            ucLength = (g_unDpRequestPool.pucData[ucArrayIndex + 1] - ucReadIndex);

            bMot = 0;
        }

        if(ScalerDpTxAuxI2CoverRead(g_unDpRequestPool.pucData[ucArrayIndex], ucLength, &(g_unDpReplyPool.stRemoteI2CRead.pucI2CRead[ucReadIndex]), bMot) == _TRUE)
        {
            ucReadIndex += ucLength;
        }
        else
        {
            // Read I2C Data Fail
            return _FALSE;
        }
    }
    while(g_unDpRequestPool.pucData[ucArrayIndex + 1] > ucReadIndex);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx I2C Over Aux Write Down Stream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
bit ScalerDpTxMstI2CWrite(void)
{
    BYTE ucLength = _DP_I2C_MAX_TRANSACTION_LENGTH;
    BYTE ucWriteIndex = 0;
    bit bMot = 1;

    do
    {
        if((GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - ucWriteIndex) <= _DP_I2C_MAX_TRANSACTION_LENGTH)
        {
            ucLength = (GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() - ucWriteIndex);

            bMot = 0;
        }

        if(ScalerDpTxAuxI2CoverWrite(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_WRITE_DEVICE_ID(), ucLength, &(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_DATA_TO_WRITE(ucWriteIndex)), bMot) == _TRUE)
        {
            ucWriteIndex += ucLength;
        }
        else
        {
            // Write I2C Data Fail
            return _FALSE;
        }
    }
    while(GET_DP_DOWN_REQUEST_REMOTE_I2C_WRITE_MSG_NUM_OF_WRITE() > ucWriteIndex);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Tx Mst Msg Count Check Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstMsgCountResetEvent(void)
{
    if(GET_DP_TX_RECEIVED_MSG_COUNT() != 0)
    {
        // Update Total Received Count
        if(GET_DP_TOTAL_RECEIVED_MSG_COUNT() >= GET_DP_TX_RECEIVED_MSG_COUNT())
        {
            SET_DP_TOTAL_RECEIVED_MSG_COUNT(GET_DP_TOTAL_RECEIVED_MSG_COUNT() - GET_DP_TX_RECEIVED_MSG_COUNT());
        }
        else
        {
            SET_DP_TOTAL_RECEIVED_MSG_COUNT(0);
            ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
        }

        // Reset Tx Received Count
        SET_DP_TX_RECEIVED_MSG_COUNT(0);
    }

    CLR_DP_TX_WAIT_DOWN_REPLY_CLEAR_PAYLOAD_ID_TABLE();
}

//--------------------------------------------------
// Description  : L = SHA-1(Stream-Status | Q_id | S_id | An | Bksv | V | M0)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstQueryEncryptionWriteShaInput(void)
{
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT3, _BIT3);

    // Reset SHA Block counter
    CLR_REG_DP_TX_SHA_ENABLE();

    // Start to Write SHA-1 Transform Input
    SET_REG_DP_TX_SHA_ENABLE();

    // 1. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(g_unDpReplyPool.pucData[1]);
    SET_REG_DP_TX_SHA_INPUT_1(g_unDpReplyPool.pucData[2]);
    SET_REG_DP_TX_SHA_INPUT_2(g_pucDPMsgQueryEncryptClientId[0]);
    SET_REG_DP_TX_SHA_INPUT_3(g_pucDPMsgQueryEncryptClientId[1]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 2. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(g_pucDPMsgQueryEncryptClientId[2]);
    SET_REG_DP_TX_SHA_INPUT_1(g_pucDPMsgQueryEncryptClientId[3]);
    SET_REG_DP_TX_SHA_INPUT_2(g_pucDPMsgQueryEncryptClientId[4]);
    SET_REG_DP_TX_SHA_INPUT_3(g_pucDPMsgQueryEncryptClientId[5]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 3. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(g_pucDPMsgQueryEncryptClientId[6]);
    SET_REG_DP_TX_SHA_INPUT_1(GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_ID());
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_AN(0));
    SET_REG_DP_TX_SHA_INPUT_3(GET_REG_DP_TX_HDCP_AN(1));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 4. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(GET_REG_DP_TX_HDCP_AN(2));
    SET_REG_DP_TX_SHA_INPUT_1(GET_REG_DP_TX_HDCP_AN(3));
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_AN(4));
    SET_REG_DP_TX_SHA_INPUT_3(GET_REG_DP_TX_HDCP_AN(5));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 5. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(GET_REG_DP_TX_HDCP_AN(6));
    SET_REG_DP_TX_SHA_INPUT_1(GET_REG_DP_TX_HDCP_AN(7));
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_BKSV(0));
    SET_REG_DP_TX_SHA_INPUT_3(GET_REG_DP_TX_HDCP_BKSV(1));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 6. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(GET_REG_DP_TX_HDCP_BKSV(2));
    SET_REG_DP_TX_SHA_INPUT_1(GET_REG_DP_TX_HDCP_BKSV(3));
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_BKSV(4));
    SET_REG_DP_TX_SHA_INPUT_3(g_pucDpTxHdcpDownStreamV[0]);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    pData[0] = 1;

    do
    {
        // 7~10. Write Data into SHA-1 Transform Input
        SET_REG_DP_TX_SHA_INPUT_0(g_pucDpTxHdcpDownStreamV[pData[0]]);
        SET_REG_DP_TX_SHA_INPUT_1(g_pucDpTxHdcpDownStreamV[pData[0] + 1]);
        SET_REG_DP_TX_SHA_INPUT_2(g_pucDpTxHdcpDownStreamV[pData[0] + 2]);
        SET_REG_DP_TX_SHA_INPUT_3(g_pucDpTxHdcpDownStreamV[pData[0] + 3]);

        // Enable write 32-bit data to SHA-1 block
        SET_REG_DP_TX_SHA_INPUT_DB();

        pData[0] += 4;
    }
    while(pData[0] < 17);

    // 11. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(g_pucDpTxHdcpDownStreamV[17]);
    SET_REG_DP_TX_SHA_INPUT_1(g_pucDpTxHdcpDownStreamV[18]);
    SET_REG_DP_TX_SHA_INPUT_2(g_pucDpTxHdcpDownStreamV[19]);
    SET_REG_DP_TX_SHA_INPUT_3(GET_REG_DP_TX_HDCP_M0(0));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 12. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(GET_REG_DP_TX_HDCP_M0(1));
    SET_REG_DP_TX_SHA_INPUT_1(GET_REG_DP_TX_HDCP_M0(2));
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_M0(3));
    SET_REG_DP_TX_SHA_INPUT_3(GET_REG_DP_TX_HDCP_M0(4));

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    // 13. Write Data into SHA-1 Transform Input
    SET_REG_DP_TX_SHA_INPUT_0(GET_REG_DP_TX_HDCP_M0(5));
    SET_REG_DP_TX_SHA_INPUT_1(GET_REG_DP_TX_HDCP_M0(6));
    SET_REG_DP_TX_SHA_INPUT_2(GET_REG_DP_TX_HDCP_M0(7));
    SET_REG_DP_TX_SHA_INPUT_3(0x80);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    for(pData[0] = 14; pData[0] < 16; pData[0]++)
    {
        // 14~15. Write 0x00 into the remaining SHA-1 Transform Input space
        SET_REG_DP_TX_SHA_INPUT_0(0x00);
        SET_REG_DP_TX_SHA_INPUT_1(0x00);
        SET_REG_DP_TX_SHA_INPUT_2(0x00);
        SET_REG_DP_TX_SHA_INPUT_3(0x00);

        // Enable write 32-bit data to SHA-1 block
        SET_REG_DP_TX_SHA_INPUT_DB();
    }

    // 16. Write 0x00 into the remaining SHA-1 Transform Input space
    SET_REG_DP_TX_SHA_INPUT_0(0x00);
    SET_REG_DP_TX_SHA_INPUT_1(0x00);
    SET_REG_DP_TX_SHA_INPUT_2(0x01);
    SET_REG_DP_TX_SHA_INPUT_3(0x98);

    // Enable write 32-bit data to SHA-1 block
    SET_REG_DP_TX_SHA_INPUT_DB();

    ScalerDpTxHDCPAuth2ShaRun(_TRUE);
}

//--------------------------------------------------
// Description  : Get DP TX SHA-1 Input Result
// Input Value  : Index
// Output Value : V
//--------------------------------------------------
BYTE ScalerDpTxMstQueryEncryptionGetShaResult(BYTE ucIndex)
{
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((4 - (ucIndex / 4)) << 5));

    return ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3 + (ucIndex % 4));
}

//--------------------------------------------------
// Description  : Compare SHA-1 Input Result L with L'
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
bit ScalerDpTxMstQueryEncryptionCompareShaResult(void)
{
    BYTE ucCnt = 0;

    for(ucCnt = 0; ucCnt < 20; ucCnt++)
    {
        // MSB first
        if(ScalerDpTxMstQueryEncryptionGetShaResult(ucCnt) != GET_DP_DOWN_REPLY_QUERY_STREAM_ENCRYPTION_STATUS_MSG_STREAM_SIGNATURE_L(ucCnt))
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Header Info. BackUp
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpTxMstDownReplyHeaderBackUp(StructTxDownReplyMsgInterleaveHeaderInfo *pstTxDownReplyMsgHeaderInfo)
{
    pstTxDownReplyMsgHeaderInfo->b4MsgLct = ((ScalerGetByte(PBD_CF_MSG_RD_DATA0) & 0xF0) >> 4);
    pstTxDownReplyMsgHeaderInfo->b4MsgLcr = (ScalerGetByte(PBD_CF_MSG_RD_DATA0) & 0x0F);

    for(pData[0] = 0; pData[0] < (pstTxDownReplyMsgHeaderInfo->b4MsgLct - 1); pData[0]++)
    {
        pstTxDownReplyMsgHeaderInfo->pucMsgRad[pData[0]] = ScalerGetByte(PBD_D0_MSG_RD_DATA1 + pData[0]);
    }

    pstTxDownReplyMsgHeaderInfo->b1MsgBroadcast = (bit)ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT7);
    pstTxDownReplyMsgHeaderInfo->b1MsgPath = (bit)ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT6);
    pstTxDownReplyMsgHeaderInfo->b1MsgMsn = (bit)ScalerGetBit(PBD_D8_MSG_RD_DATA9, _BIT4);
}

//--------------------------------------------------
// Description  : Check SBMSG Header Info. Consistent
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
bit ScalerDpTxMstDownReplySidebandMsgHeaderCheck(StructTxDownReplyMsgInterleaveHeaderInfo stTxDownReplyMsgHeaderInfo)
{
    if(stTxDownReplyMsgHeaderInfo.b4MsgLct != ((ScalerGetByte(PBD_CF_MSG_RD_DATA0) & 0xF0) >> 4))
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b4MsgLcr != (ScalerGetByte(PBD_CF_MSG_RD_DATA0) & 0x0F))
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgBroadcast != (bit)ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT7))
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgPath != (bit)ScalerGetBit(PBD_D7_MSG_RD_DATA8, _BIT6))
    {
        return _FALSE;
    }

    if(stTxDownReplyMsgHeaderInfo.b1MsgMsn != (bit)ScalerGetBit(PBD_D8_MSG_RD_DATA9, _BIT4))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Down Reply SBMSG Interleave Proc
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpTxMstDownReplySideBandMsgProc(void)
{
    if((GET_REG_DP_TX_UPSTREAM_SBMSG_START_OF_BIT() == _TRUE) && (GET_REG_DP_TX_UPSTREM_MSG_HEADER_CRC_STATUS() == _TRUE))
    {
        if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0)
        {
            // BacKup Interleave0 Header
            ScalerDpTxMstDownReplyHeaderBackUp(&g_stTxMsgBackupHeaderInfo0);
        }
        else if(GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0)
        {
            // BacKup Interleave1 Header
            ScalerDpTxMstDownReplyHeaderBackUp(&g_stTxMsgBackupHeaderInfo1);

            // Set SBMSG Interleave Flag
            SET_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();
        }

        SET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT(GET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() + 1);
    }

    if(ScalerDpTxMstDownReplySidebandMsgHeaderCheck(g_stTxMsgBackupHeaderInfo0) == _TRUE)
    {
        // Get Interleave0 Data
        SET_REG_DP_TX_UPSTREAM_MSG_READ_PTR(0x00);

        for(pData[0] = 0; pData[0] < ScalerGetByte(PBD_DF_BUF_FW_WRPTR); pData[0]++)
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA(GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(), GET_REG_DP_TX_UPSTREAM_MSG_READ_DATA());

            SET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH(GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() + 1);
        }

        if(GET_REG_DP_TX_UPSTREAM_SBMSG_END_OF_BIT() == _TRUE)
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();

            SET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(GET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() + 1);
        }

        if(GET_REG_DP_TX_UPSTREM_MSG_CRC_STATUS() != (_BIT1 | _BIT0))
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
        }

        // Buf_CLR=1 WR_PTR = 0x00
        CLR_REG_DP_TX_UPSTREAM_MSG_BUF();
    }
    else if(ScalerDpTxMstDownReplySidebandMsgHeaderCheck(g_stTxMsgBackupHeaderInfo1) == _TRUE)
    {
        SET_REG_DP_TX_UPSTREAM_MSG_READ_PTR(0x00);

        for(pData[0] = 0; pData[0] < ScalerGetByte(PBD_DF_BUF_FW_WRPTR); pData[0]++)
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA(GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(), GET_REG_DP_TX_UPSTREAM_MSG_READ_DATA());

            SET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH(GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() + 1);
        }

        if(GET_REG_DP_TX_UPSTREAM_SBMSG_END_OF_BIT() == _TRUE)
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();

            SET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT(GET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() + 1);
        }

        if(GET_REG_DP_TX_UPSTREM_MSG_CRC_STATUS() != (_BIT1 | _BIT0))
        {
            SET_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
        }

        // Buf_CLR=1 WR_PTR = 0x00
        CLR_REG_DP_TX_UPSTREAM_MSG_BUF();
    }

    if(((GET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() == 1) && (GET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() == 1)) ||
       ((GET_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT() == 2) && (GET_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT() == 2)))
    {
        // CLR Start/End Of Bit Count
        CLR_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT();
        CLR_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT();

        // Disable Tx DownReply Read
        SET_DP_TX_DOWN_REPLY_READ_DISABLE();
    }
}

//--------------------------------------------------
// Description  : Down Reply Interleave Finish Check
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpTxMstDownReplyInterleaveFinishCheck(void)
{
    if(GET_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH() == _TRUE)
    {
        CLR_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();

        CLR_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    }
    else
    {
        CLR_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();

        CLR_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    }

    if((GET_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH() == 0) && (GET_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH() == 0))
    {
        // CLR SBMSG Interleave Flag
        CLR_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();

        // TX Read Enable
        CLR_DP_TX_DOWN_REPLY_READ_DISABLE();
    }
}

//--------------------------------------------------
// Description  : Clear Down Reply Interleave Flag
// Input Value  : None
// Output Value : Result
//--------------------------------------------------
void ScalerDpTxMstClrDownReplyInterleaveFlag(void)
{
    CLR_DP_TX_MSG_DOWN_REPLY_SBMSG_INTERLEAVE();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF0_MSG_FINISH();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF1_MSG_FINISH();
    CLR_DP_TX_MSG_DOWN_REPLY_START_OF_BIT_COUNT();
    CLR_DP_TX_MSG_DOWN_REPLY_END_OF_BIT_COUNT();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF0_DATA_LENGTH();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF1_DATA_LENGTH();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF0_CRC_FAILURE();
    CLR_DP_TX_MSG_DOWN_REPLY_BUF1_CRC_FAILURE();
    g_stTxMsgBackupHeaderInfo0.b4MsgLct = 0;
    g_stTxMsgBackupHeaderInfo1.b4MsgLct = 0;
}

//--------------------------------------------------
// Description  : DP Tx Mst Reset
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxMstReset(void)
{
// HW Reset-----------------------------------

    // MSTM_CTRL reset
    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
    {
        pData[0] = 0x00;

        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, pData);
    }

    // AUX fifo reset
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Reset Tx MSG FIFO
    SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_PTR(0x00);

    // Reset Tx Write MSG FSM
    SET_REG_DP_TX_DOWNSTREAM_MSG_WRITE_DISABLE();

    // Reset Tx Read MSG FSM
    SET_REG_DP_TX_UPSTREAM_MSG_READ_DISABLE();

// FW Reset-----------------------------------

    SET_DP_TX_DOWN_REQUEST_EVENT(_DP_TX_NONE_EVENT);

    // CLR TX Read Buffer Status
    SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

    // Enable Tx Down Reply Read
    CLR_DP_TX_DOWN_REPLY_READ_DISABLE();

    SET_DP_TOTAL_RECEIVED_MSG_COUNT(0);

    SET_DP_TX_RECEIVED_MSG_COUNT(0);

    // Clear Flags of Tx MSG Proc Status
    CLR_DP_TX_DOWN_REQUEST_ANAL();

    CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();

    CLR_DP_TX_MSG_DOWN_REQUEST_ANAL_FINISH();

    CLR_DP_TX_DOWN_REQUEST_MSG_DONE();

    CLR_DP_TX_DOWN_REPLY_DIRECTLY();

    CLR_DP_TX_DOWN_REPLY_ANAL();

    CLR_DP_TX_MSG_DOWN_REPLY_ANAL_FINISH();

    // Cancel Timers
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_RX_MSG_COUNT_RESET_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
    ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
}

#endif // End for #if((_DP_MST_SUPPORT == _ON) && (_DP_TX_SUPPORT == _ON))

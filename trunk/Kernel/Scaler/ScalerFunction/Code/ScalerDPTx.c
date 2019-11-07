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
// ID Code      : ScalerDPTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DP_TX__

#include "ScalerFunctionInclude.h"

#if(_DP_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DP_TX_SST_TU_SIZE                          32

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDPTxModeInfoType g_stTxModeInfo;
StructDPTxInputInfo g_stTxInputInfo;
EnumDPTxIRQEventType g_enumDpTxIRQType = _DP_TX_IRQ_HPD_NONE;
EnumDPTxIRQEventType g_enumDpTxIRQTypeInt = _DP_TX_IRQ_HPD_NONE;
EnumDPTxTRQEventHDCPType g_enumDpTxIRQHDCPType = _DP_TX_IRQ_HDCP_NONE;
StructTimingInfo g_stDPTxInputTimingInfo;
StructDPTxHDCPAuthInfo g_stTxHDCPAuthInfo;
BYTE g_pucDpTxHdcpKsvFifo[_DP_TX_HDCP_DEVICE_COUNT_MAX * 5];
BYTE g_pucDpTxHdcpDownStreamV[20];

bit g_bDpTxIRQHPDDetected = _FALSE;
bit g_bDpTxSourceChanged = _FALSE;
BYTE g_ucDpTxStreamSource = _DP_TX_SOURCE_NONE;
BYTE g_ucDpTxCtsRequestType = _DP_TX_CTS_NONE;

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
bit g_bDpTxVscSdpColorMode;
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//--------------------------------------------------
void ScalerDpTxModeHandler(void);
void ScalerDpTxJudgeHandler(void);
void ScalerDpTxInitial(void);
void ScalerDpTxStateChangeEvent(EnumDPTxModeStatus enumModeState);
void ScalerDpTxIntHandle_EXINT0(void);
void ScalerDpTxHPDProc(void);
void ScalerDpTxIRQEventCheck(void);
bit ScalerDpTxLinkConfig(void);
void ScalerDpTxStreamHandler(void);
void ScalerDpTxSetStreamSource(EnumDPTxInputSource enumStreamSource);
void ScalerDpTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource);
void ScalerDpTxSSTSetting(void);
void ScalerDpTxAudioSetting(void);
bit ScalerDpTxAudioGetChannelChange(void);
WORD ScalerDpTxAudioGetSamplingFreqPacket(void);
void ScalerDpTxSetSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
void ScalerDpTxClearSecDataHeader(EnumDPTxSecDataPacketType enumPackettype);
BYTE ScalerDpTxAudioGetSecDataParity(BYTE ucHeader);
void ScalerDpTxSSTDisplayFormatSetting(void);
void ScalerDpTxSSTMSASetting(void);
void ScalerDpTxLinkTraining(void);
void ScalerDpTxTPInitialSet(void);
BYTE ScalerDpTxTrainPattern1(void);
bit ScalerDpTxTP1Lane0Adjust(void);
bit ScalerDpTxTP1Lane1Adjust(void);
bit ScalerDpTxTP1Lane2Adjust(void);
bit ScalerDpTxTP1Lane3Adjust(void);
BYTE ScalerDpTxTrainPattern2(void);
void ScalerDpTxTP2Lane0Adjust(void);
void ScalerDpTxTP2Lane1Adjust(void);
void ScalerDpTxTP2Lane2Adjust(void);
void ScalerDpTxTP2Lane3Adjust(void);
bit ScalerDpTxLinkRateReduce(EnumDPTxLTResult enumDPTxLTResult);
bit ScalerDpTxLaneCountReduce(EnumDPTxLTResult enumDPTxLTResult);
void ScalerDpTxTrainPatternEnd(void);
void ScalerDpTxSignalReset(void);

// SSC bug of PI for RLE0638
void ScalerDpTxSSCSet(bit bSSCEn);
void ScalerDpTxAuxPHYSet(BYTE ucMode);
void ScalerDpTxSignalInitialSetting(void);
void ScalerDpTxSignalLaneSetting(void);

bit ScalerDpTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV);
bit ScalerDpTxMeasureInputInfo(void);

bit ScalerDpTxCloneCheckInterlaceVtotal(void);
void ScalerDpTxCloneOutputProc(BYTE ucInputPort, BYTE ucPortType, bit bClone);
BYTE ScalerDpTxCloneGetCurrentInputPort(void);

#if(_DP_MST_SUPPORT == _ON)
bit ScalerDpTxGenConnectStatusNotifyMsgCheck(void);
bit ScalerDpTxSinkCountUpdate(void);
#endif

void ScalerDpTxHDCPHandler(void);
void ScalerDpTxHDCPCheckDownstreamCapability(void);
bit ScalerDpTxHDCPAuth1Proc(void);
bit ScalerDpTxHDCPAuth1CheckBksv(void);
void ScalerDpTxHDCPAuth1GenAn(void);
void ScalerDpTxHDCPAuth1WriteAnAkey(void);
bit ScalerDpTxHDCPAuth1GenKm(void);
bit ScalerDpTxHDCPAuth1CompareR0(void);
bit ScalerDpTxHDCPAuth2Proc(void);
void ScalerDpTxHDCPAuth2WriteShaInput(void);
void ScalerDpTxHDCPAuth2ShaRun(bit bIsFirst);
bit ScalerDpTxHDCPCheckBinfo(void);
bit ScalerDpTxHDCPAuth2CompareV(void);
void ScalerDpTxHDCPChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState);
void ScalerDpTxHDCPTimeoutToReadR0Event(void);
void ScalerDpTxHDCPTimeoutForVReadyEvent(void);
void ScalerDpTxHDCPPollingVReadyEvent(void);
EnumDPTxTRQEventHDCPType ScalerDpTxHDCPPollingCpIrqType(void);
void ScalerDpTxHDCPEncryptSignalProc(bit bEnable);
void ScalerDpTxHDCPResetInfo(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Mode Handler
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxModeHandler(void)
{
    // Get Rx Cap if Rx Cap Changed IRQ Received
    if((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG) && (GET_DP_TX_DOWNSTREAM_INFO_READY() == _FALSE))
    {
        // Get Downstream Link Configuration
        if(ScalerDpTxLinkConfig() == _TRUE)
        {
            SET_DP_TX_DOWNSTREAM_INFO_READY();
        }
    }

#if(_DP_MST_SUPPORT == _ON)

    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        if(ScalerDpTxGenConnectStatusNotifyMsgCheck() == _TRUE)
        {
            CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

            if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG)
            {
                // Set 1s to Notify as to avoid DownRequest MSG traffic things
                ScalerTimerActiveTimerEvent(SEC(1), _SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
            }
            else
            {
                // Clear Up_Req Bypass MSG Back Up
                CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

                // Align Reported Cable Status with Tx Cable Status
                SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS());

                // Initiate Connection Status Notify
                SET_DP_GEN_UP_REQUEST_MSG(_DP_MSG_CONNECTION_STATUS_NOTIFY);
            }

            CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();
        }

        if(GET_DP_RX_SELF_GEN_UP_REQUEST_RETRY() == _DP_MSG_CONNECTION_STATUS_NOTIFY)
        {
            CLR_DP_RX_SELF_GEN_UP_REQUEST_RETRY();

            ScalerTimerActiveTimerEvent(SEC(2), _SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);
        }

        if((GET_DP_TX_DOWNSTREAM_DPCD_REV() == _DP_VERSION_1_2) && (GET_DP_TX_DOWNSTREAM_MSGCAP_STATUS() == _DP_MSG_SUPPORT))
        {
            if(GET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS() != (bit)(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1))
            {
                if(ScalerDpTxAuxNativeRead(0x00, 0x01, 0x11, 1, pData) == _TRUE)
                {
                    pData[0] = (pData[0] & ~_BIT1) | (GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1);

                    if(ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, pData) == _TRUE)
                    {
                        SET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS((bit)(pData[0] & _BIT1));
                    }
                }
            }
        }
    }
#endif

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                // Power Down ML PHY
                ScalerGDIPhyTxMLPowerOff();

                // Reset Daisy Chian ST3 ~ ST5
                SET_REG_DP_RX_DAIZY_ST3_START(0x00);
                SET_REG_DP_RX_DAIZY_ST3_END(0x00);
                SET_REG_DP_RX_DAIZY_ST4_START(0x00);
                SET_REG_DP_RX_DAIZY_ST4_END(0x00);
                SET_REG_DP_RX_DAIZY_ST5_START(0x00);
                SET_REG_DP_RX_DAIZY_ST5_END(0x00);

                // Reset TX Buffer Status
                SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

                // Update Total Received Count
                if((GET_DP_TOTAL_RECEIVED_MSG_COUNT() >= GET_DP_TX_RECEIVED_MSG_COUNT()) && (GET_DP_TX_RECEIVED_MSG_COUNT() > 0))
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

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_MSG_COUNT_RESET_EVENT);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_CABLE_STATUS_CHANGE_EVENT);

                SET_DP_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_UNPLUG);
                SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_NO_DEVICE);
                SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);

                SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                CLR_DP_TX_DOWNSTREAM_TP3_SUPPORT();

                CLR_DP_TX_DOWNSTREAM_INFO_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
                CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();
                CLR_DP_TX_HDCP_AUTH_START();
                CLR_DP_TX_HDCP_AUTH_HOLD();

                // CLR TX Read Buffer Status
                SET_DP_TX_RD_BUFFER_STATUS(_DP_TX_READ_BUF_EMPTY);

                CLR_DP_TX_DOWN_REPLY_READ_DISABLE();

#if(_DP_MST_SUPPORT == _ON)
                // Set Rx Sink Count
                SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, 0x41);

                CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

                // Clear Up_Req Bypass MSG Back Up
                CLR_DP_TX_UP_REQUEST_BACKUP_DATA();
#endif
                CLR_DP_RX_WAIT_REMOTE_LINK_ADDRESS_REPLY();
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
#if(_DP_MST_SUPPORT == _ON)
                // Reset MST Related Status
                SET_DP_TX_LINK_PBN_PER_TIMESOLT(0);

                // Clear All ST3 ~ ST5 Time Slot
                for(pData[0] = 0; pData[0] < 3; pData[0]++)
                {
                    // CLR Daisy Chain Timeslot
                    ScalerSetBit((GET_DP_TX_STX_START_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                    ScalerSetBit((GET_DP_TX_STX_END_ADDRESS(pData[0] + 2)), ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
                }

#endif  // End of #if(_DP_MST_SUPPORT == _ON)

                SET_DP_TX_DOWNSTREAM_DPPLUG_STATUS(_DP_PLUG);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpTxLinkTraining();
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            if(GET_DP_TX_MODE_STATE_CHANGE() == _TRUE)
            {
                if(GET_DP_TX_HDCP_AUTH_START() == _FALSE)
                {
                    SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);
                }
            }

            ScalerDpTxStreamHandler();

#if(_DP_MST_SUPPORT == _ON)

            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) || (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST))
            {
                // ScalerDpTxMonitorDownstreamBW();
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : DP Tx Mode Judge
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxJudgeHandler(void)
{
    CLR_DP_TX_MODE_STATE_CHANGE();

    switch(GET_DP_TX_MODE_STATE())
    {
        case _DP_TX_MODE_STATUS_UNPLUG:

            if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_PLUG_EVENT)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_INITIAL);
            }

            break;

        case _DP_TX_MODE_STATUS_INITIAL:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            if(GET_DP_TX_DOWNSTREAM_INFO_READY() == _TRUE)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_TRAINING:

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_ON);
            }

            // HPD short plug event && Link status fail
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        case _DP_TX_MODE_STATUS_LINK_ON:

            // HPD short plug event && Link status fail
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
                CLR_DP_TX_DOWNSTREAM_INFO_READY();
            }

            // For Link CTS test
            if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
            {
                ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
            }

            break;

        default:

            break;
    }

    if(GET_DP_TX_HPD_EVENT() == _DP_TX_HPD_UNPLUG_EVENT)
    {
        ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_UNPLUG);
    }

    if(GET_DP_TX_FORCE_LINK_TRAINING() == _TRUE)
    {
        CLR_DP_TX_FORCE_LINK_TRAINING();

        if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
        {
            ScalerDpTxStateChangeEvent(_DP_TX_MODE_STATUS_LINK_TRAINING);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxInitial(void)
{
    // Setting Aux
    ScalerDpTxAuxPHYSet(_DP_TX_AUX_DIFF_MODE);

    // For HDCP Auth
    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

    // Set ECF by FW mode
    ScalerSetBit(PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);

    // Set Aux Timeout
    ScalerSetByte(PBD_A1_AUX_TIMEOUT, 0x95);

    // Power Down ML PHY
    ScalerGDIPhyTxMLPowerOff();

    // Power CMU PHY
    ScalerGDIPhyTxCMUPowerOff();

    // Power On Aux CH
    ScalerSetBit(PBD_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);

    // Sync end Pattern Error Handle Disable
    ScalerSetBit(PBD_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);

    SET_DP_TX_HPD_FIRST_PLUG();

    // Set HPD 1ms Timer to  2ms
    ScalerSetBit(PBB_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
    ScalerSetByte(PBB_75_HPD_TIMER3, 0x2C);

    // Set HPD 10ms Timer to  2ms
    ScalerSetByte(PBB_78_HPD_TIMER6, 0x0D);
    ScalerSetByte(PBB_79_HPD_TIMER7, 0x2C);

    // Enable HPD Detection
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, 0x00);
    ScalerSetBit(PBB_70_HPD_CTRL, ~_BIT7, _BIT7);

    // Clear HPD IRQ Flag
    ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);

    // Clear IRQ HPD Type Flag
    CLR_DP_TX_IRQ_HPD_TYPE();
    CLR_DP_TX_IRQ_HPD_TYPE_INT();
    CLR_DP_TX_IRQ_HPD_DETECTED();
    CLR_DP_TX_IRQ_HDCP_TYPE();

    // Enable Short IRQ and Disable Long IRQ
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);

    // Set Initial HPD Status
    SET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS(GET_DP_TX_HPD_DEBOUNCE_LEVEL());

#if(_DP_MST_SUPPORT == _ON)

    CLR_DP_TX_UP_REQUEST_BYPASS_REGEN();

    // Clear Up_Req Bypass MSG Back Up
    CLR_DP_TX_UP_REQUEST_BACKUP_DATA();

    // HW will auto calculate Start and End
    SET_REG_DP_TX_DOWNSTREAM_MSG_AUTO_MODE();

    // Set TX MSG Aux Write Burst Length 16bytes
    SET_REG_DP_TX_DOWNSTREAM_MSG_BURST_LENGTH(_DP_TX_AUX_WRITE_BURST_LENGTH);

    // Enable Only Read One SBMSG
    ScalerSetBit(PBD_CA_AUX_TX_MSG_RD_CTRL, ~_BIT5, _BIT5);

    // Set TX MSG Aux Read Burst Length 16bytes
    SET_REG_DP_TX_UPSTREAM_MSG_READ_BURST_LENGTH(_DP_TX_AUX_READ_BURST_LENGTH);

    // Enable DP Tx Link Clock
    ScalerDpTxMstLinkClockEn(_ENABLE);

    // Mst Port Select
    ScalerDpRxMstPortSel();
#endif

    // Disable Downstream Z0 Detection
    ScalerSetBit(PBC_A2_DPTX_RCV_DET0, ~_BIT6, 0x00);

    // Set DP TX CLK divider
    ScalerSetByte(PBB_E0_DPTX_CLK_GEN, 0x21);

    // Enable Arbiter Stuffing and Framing
    ScalerSetBit(PBB_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

    // Clear HDCP Flag
    CLR_DP_TX_HDCP_AUTH_START();
    CLR_DP_TX_HDCP_AUTH_HOLD();

    // Clear Audio Flag
    CLR_DP_TX_AUDIO_READY_TO_PLAY();
    CLR_DP_TX_CURRENT_AUDIO_FREQUENCY();

    // Clear Link CTS Request Type
    CLR_DP_TX_CTS_TEST_REQUEST_TYPE();
}

//--------------------------------------------------
// Description  : Switch to Active State
// Input Value  : Target Tx Mode
// Output Value : None
//--------------------------------------------------
void ScalerDpTxStateChangeEvent(EnumDPTxModeStatus enumModeState)
{
    SET_DP_TX_MODE_STATE(enumModeState);
    SET_DP_TX_MODE_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Tx INT Handle
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxIntHandle_EXINT0(void) using 1
{
    // Short HPD IRQ
    if((ScalerGetBit_EXINT(PBB_72_HPD_IRQ_EN, _BIT6) == _BIT6) &&
       (ScalerGetBit_EXINT(PBB_71_HPD_IRQ, _BIT6) == _BIT6))
    {
        ScalerSetBit_EXINT(PBB_71_HPD_IRQ, ~(_BIT6 | _BIT4 | _BIT2), _BIT6);

        if(ScalerDpTxAuxNativeRead_EXINT0(0x00, 0x02, 0x00, 6, pData_EXINT) == _TRUE)
        {
            SET_DP_TX_IRQ_HPD_DETECTED();

            if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 1) && ((pData_EXINT[2] & 0x07) != 0x07)) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 2) && ((pData_EXINT[2] & 0x77) != 0x77)) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == 4) && (((pData_EXINT[2] & 0x77) != 0x77) || ((pData_EXINT[3] & 0x77) != 0x77))) ||
               ((GET_DP_TX_DOWNSTREAM_LANE_NUM() != 1) && ((pData_EXINT[4] & 0x01) != 0x01)))
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
            }

            if((pData_EXINT[1] & _BIT2) == _BIT2)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
            }

            if((pData_EXINT[1] & _BIT1) == _BIT1)
            {
                SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
            }
        }

        if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= 0x12)
        {
            // Get IRQ Event Status Indicator
            if(ScalerDpTxAuxNativeRead_EXINT0(0x00, 0x20, 0x03, 3, pData_EXINT) == _TRUE)
            {
                SET_DP_TX_IRQ_HPD_DETECTED();

                if((pData_EXINT[0] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);
                }

                if((pData_EXINT[0] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_CP_IRQ);
                }

                if((pData_EXINT[0] & _BIT3) == _BIT3)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_MCCS_IRQ);
                }

                if(((pData_EXINT[0] & _BIT4) == _BIT4) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_DOWN_REPLY_READY_IRQ);
                }

                if(((pData_EXINT[0] & _BIT5) == _BIT5) && (GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ) == 0x00))
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_UP_REQUEST_READY_IRQ);
                }

                if((pData_EXINT[2] & _BIT0) == _BIT0)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ);
                }

                if((pData_EXINT[2] & _BIT1) == _BIT1)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                }

                if((pData_EXINT[2] & _BIT2) == _BIT2)
                {
                    SET_DP_TX_IRQ_HPD_TYPE_INT(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx HPD Detection
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHPDProc(void)
{
    SET_DP_TX_HPD_EVENT(_DP_TX_HPD_NO_EVENT);
    CLR_DP_TX_IRQ_HPD_TYPE();

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Record which kind of HPD Change happened by now
    pData[0] = (ScalerGetByte(PBB_71_HPD_IRQ) | ((BYTE)GET_DP_TX_IRQ_HPD_DETECTED() << 6));

    // Copy IRQ type Detected In INT
    SET_DP_TX_IRQ_HPD_TYPE(GET_DP_TX_IRQ_HPD_TYPE_INT());

    CLR_DP_TX_IRQ_HPD_DETECTED();

    // Clear IRQ type of Int.
    CLR_DP_TX_IRQ_HPD_TYPE_INT();

    // Determine Current HPD Event Status
    // Current HPD Level HIGH
    if(GET_DP_TX_HPD_DEBOUNCE_LEVEL() == _HIGH)
    {
        // First HPD From Low to High
        if(GET_DP_TX_HPD_FIRST_PLUG() == _TRUE)
        {
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            CLR_DP_TX_HPD_FIRST_PLUG();
        }

        if((pData[0] & _BIT4) == _BIT4)
        {
            // HPD unplug Event
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clear Unplug Flag
            ScalerSetBit(PBB_71_HPD_IRQ, ~(_BIT7 | _BIT6 | _BIT5 | _BIT3 | _BIT2 | _BIT1), _BIT4);
        }
        else if((pData[0] & _BIT2) == _BIT2)
        {
            // Long HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_PLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
        else if((pData[0] & _BIT6) == _BIT6)
        {
            // Short HPD
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_IRQ_EVENT);
        }
    }
    else
    {
        if((pData[0] & _BIT4) == _BIT4)
        {
            // HPD unplug Event
            SET_DP_TX_HPD_EVENT(_DP_TX_HPD_UNPLUG_EVENT);

            // Clr All flag
            ScalerSetByte(PBB_71_HPD_IRQ, 0xFE);
        }
    }

    switch(GET_DP_TX_HPD_EVENT())
    {
        case _DP_TX_HPD_PLUG_EVENT:

            CLR_DP_TX_DOWNSTREAM_INFO_READY();

            break;

        case _DP_TX_HPD_IRQ_EVENT:

            // Check Short HPD IRQ Type
            ScalerDpTxIRQEventCheck();

            break;

        case _DP_TX_HPD_UNPLUG_EVENT:

            break;

        default:
            break;
    }

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);
}

//--------------------------------------------------
// Description  : Dp Tx Link Maintance
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxIRQEventCheck(void)
{
    BYTE pucData[4];

    memset(pucData, 0, sizeof(pucData));

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
    {
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ) == _DP_TX_IRQ_HPD_RX_CAP_CHG_IRQ)
        {
            pucData[0] |= _BIT0;
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT1;

            // Get Link Status
            ScalerDpTxAuxNativeRead(0x00, 0x20, 0x0C, 3, &pucData[1]);

            switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
            {
                case _DP_ONE_LANE:
                    if((pucData[1] & 0x07) == 0x07)
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_TWO_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                case _DP_FOUR_LANE:
                    if(((pucData[1] & 0x77) == 0x77) && ((pucData[2] & 0x77) == 0x77) && ((pucData[3] & 0x01) == 0x01))
                    {
                        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ);
                    }
                    break;

                default:
                    break;
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_STREAM_STATUS_CHG_IRQ);
            }
        }

        // CLR Rx_Cap_IRQ and Link_Status_CHG_IRQ and Stream_Status_CHG_IRQ
        if(pucData[0] != 0x00)
        {
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x05, 1, pucData);
        }

        pucData[0] = 0x00;

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            pucData[0] |= _BIT2;

            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
                // Read HDCP B Status
                if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                {
                    SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                }
            }
        }

        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_MCCS_IRQ) == _DP_TX_IRQ_HPD_MCCS_IRQ)
        {
            pucData[0] |= _BIT3;
        }
    }
    else
    {
        // CLR CP IRQ
        if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_CP_IRQ) == _DP_TX_IRQ_HPD_CP_IRQ)
        {
            if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ) == _DP_TX_IRQ_HPD_LINK_STATUS_CHG_IRQ)
            {
                CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_CP_IRQ);
            }
            else
            {
                // Read HDCP B Status
                if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, &pucData[1]) == _TRUE)
                {
                    SET_DP_TX_IRQ_HDCP_TYPE(pucData[1]);
                }
            }

            pucData[0] |= _BIT2;
        }
    }

    if(GET_DP_TX_IRQ_HPD_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST) == _DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST)
    {
        CLR_DP_TX_IRQ_HPD_TARGET_TYPE(_DP_TX_IRQ_HPD_AUTOMATED_TEST_REQUEST);

        pucData[0] |= _BIT1;

        // Read CTS Test Request Type
        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x18, 1, &pucData[1]) == _TRUE)
        {
            SET_DP_TX_CTS_TEST_REQUEST_TYPE(pucData[1]);
        }

        // Support TEST_LINK_TRAINING
        if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
        {
            pucData[1] = _TEST_ACK;
        }
        else
        {
            pucData[1] = _TEST_NAK;

            CLR_DP_TX_CTS_TEST_REQUEST_TYPE();
        }

        // Write TEST Response
        ScalerDpTxAuxNativeWrite(0x00, 0x02, 0x60, 1, &pucData[1]);
    }

    if(pucData[0] != 0x00)
    {
        if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2)
        {
            // CLR CP_IRQ and MCCS_IRQ
            ScalerDpTxAuxNativeWrite(0x00, 0x20, 0x03, 1, pucData);
        }

        // CLR CP_IRQ and AUTOMATED_TEST_REQUEST
        ScalerDpTxAuxNativeWrite(0x00, 0x02, 0x01, 1, pucData);
    }
}

//--------------------------------------------------
// Description  : Dp Tx Read DPCD Rx Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxLinkConfig(void)
{
    BYTE pucData[16];

    memset(pucData, 0, sizeof(pucData));

    // Write OUI interactive
    pucData[0] = 0x4C;
    pucData[1] = 0xE0;
    pucData[2] = 0x00;
    if(ScalerDpTxAuxNativeWrite(0x00, 0x03, 0x00, 3, pucData) == _FALSE)
    {
        return _FALSE;
    }

    if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x00, 16, pucData) == _FALSE)
    {
        return _FALSE;
    }

    DebugMessageDigital("1. ScalerDpTxAuxNativeRead", pucData[0]);
    DebugMessageDigital("1. ScalerDpTxAuxNativeRead", pucData[1]);
    DebugMessageDigital("1. ScalerDpTxAuxNativeRead", pucData[2]);
    DebugMessageDigital("1. ScalerDpTxAuxNativeRead", pucData[3]);
    DebugMessageDigital("1. ScalerDpTxAuxNativeRead", pucData[4]);

    // Step1:Get DownStream infromation
    if((pucData[0] != 0x10) && (pucData[0] != 0x11) && (pucData[0] != 0x12))
    {
        pucData[0] = 0x11;
    }

    SET_DP_TX_DOWNSTREAM_DPCD_REV(pucData[0]);

    if(pucData[0] == 0x12)
    {
        // Disable Downstream MST Mode
        pucData[10] = 0x00;
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, &pucData[10]);

        // Check TP3 support
        if((pucData[2] & _BIT6) == _BIT6)
        {
            SET_DP_TX_DOWNSTREAM_TP3_SUPPORT();
        }
        else
        {
            CLR_DP_TX_DOWNSTREAM_TP3_SUPPORT();
        }

        if(ScalerDpTxAuxNativeRead(0x00, 0x00, 0x21, 1, (pucData + 10)) == _FALSE)
        {
            return _FALSE;
        }

        // MST_CAP = 1
        if((pucData[10] & _BIT0) == _BIT0)
        {
            // Set link Address Reply information
            SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_MST_OR_SST_BRANCH_DOWNSTREAM);
            SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_SUPPORT);
            SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);

            if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
            {
                SET_DP_TX_DOWNSTREAM_UP_REQUEST_CAP_STATUS((bit)(GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1));

                // Modify Downstream MST Mode
                pucData[10] = (GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1);
                ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, &pucData[10]);
            }
        }
        else // MST_CAP = 0
        {
            SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);

            if((pucData[4] & _BIT0) == 1)
            {
                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP(1);

                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(1);
            }
            else
            {
                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP(0);

                SET_DP_TX_DOWNSTREAM_NUMBER_OF_SDP_SINK(0);
            }

            if((pucData[5] & _BIT0) == 1)
            {
                // Link CTS 4.2.2.7 start
                if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, (pucData + 11)) == _FALSE)
                {
                    return _FALSE;
                }
                // Link CTS 4.2.2.7 end

                if((pucData[5] & 0x06) == _DP_TYPE) // MST Device with Branching Unit
                {
                    SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_MST_OR_SST_BRANCH_DOWNSTREAM);
                    SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
                }
                else // SST Legacy Converter Device
                {
                    SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_TO_LEGACY);
                    SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_PLUG);
                }
            }
            else // SST Sink Device
            {
                SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_SST_SINK);
                SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
            }
        }
    }
    else // DPCD Revision 1.0/1.1
    {
        SET_DP_TX_DOWNSTREAM_PEERDEVICE_TYPE(_DP_SST_SINK);
        SET_DP_TX_DOWNSTREAM_MSGCAP_STATUS(_DP_MSG_NO_SUPPORT);
        SET_DP_TX_DOWNSTREAM_LEGACYPLUG_STATUS(_DP_UNPLUG);
    }

    // Step2:Get link Rate
    if((pucData[1] == 0x06) || (pucData[1] == 0x0A) || ((pucData[0] == 0x12) && (pucData[1] == 0x14)))
    {
        SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(pucData[1]);
    }
    else // Set the slowest link rate
    {
        SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(0x06);
    }

    SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM((pucData[2] & 0x1F));

    SET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING((bit)(pucData[2] & _BIT7));

    SET_DP_TX_DOWNSTREAM_DOWN_SPREAD((bit)(pucData[3] & _BIT0));

#if(_DP_MST_SUPPORT == _ON)

    if(ScalerDpTxSinkCountUpdate() == _FALSE)
    {
        DebugMessageMst("Tx Sink Count Update Fail", 0);

        return _FALSE;
    }
#endif

    ScalerDpTxHDCPCheckDownstreamCapability();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Handle Tx Output stream
// Input Value  : DP Tx Input Source
// Output Value : None
//--------------------------------------------------
void ScalerDpTxStreamHandler(void)
{
    if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) && (GET_REG_DP_RX_MST_ENABLE() == _FALSE))
    {
        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
    }

    if(GET_DP_TX_STREAM_SOURCE_CHANGE() == _TRUE)
    {
        CLR_DP_TX_STREAM_SOURCE_CHANGE();

        switch(GET_DP_TX_STREAM_SOURCE())
        {
            case _DP_TX_SOURCE_NONE:

                if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
                {
                    ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

                    ScalerTimerDelayXms(2);
                }

                if((GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_PLUG) && (GET_DP_TX_DOWNSTREAM_DPCD_REV() >= _DP_VERSION_1_2))
                {
                    ScalerDpTxAuxNativeRead(0x00, 0x01, 0x11, 1, pData);

                    if((pData[0] & _BIT0) == _BIT0)
                    {
                        pData[0] &= ~_BIT0;
                        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, pData);
                    }
                }

                // Main Link switch to IDLE Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

                // Direct Apply Idle Pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                // Set Standalong Audio
                ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_OFF);

                break;

            case _DP_TX_SOURCE_MST:

                // Disable Audio
                ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_OFF);

#if(_DP_FREESYNC_SUPPORT == _ON)
                ScalerDpTxSSTSetAmdSpdInfo(_OFF);
#endif

                // Enable Downstream MST Mode
                pData[0] = ((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) | _BIT0);
                ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, pData);

                // Switch MST Daisy Chain From Rx0 or Rx1
                ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT0, ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? 0x00 : _BIT0));

                // Phy Input Data from Daizy chain (MST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, _BIT1);

                break;

            case _DP_TX_SOURCE_MST2SST:

                // Switch MST Daisy Chain From Rx0 or Rx1 for MST to SST Audio
                ScalerSetBit(PBB_D9_DPTX_TOP_CTL, ~_BIT0, ((g_enumDpMSTCapablePort == _DP_MST_RX0_PORT) ? 0x00 : _BIT0));

                // Setting DP TX MAC
                ScalerDpTxSSTSetting();

                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                break;

            case _DP_TX_SOURCE_CLONE:

                // Setting DP TX MAC
                ScalerDpTxSSTSetting();

                // Main Link switch to VIDEO pattern
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_VIDEO_PATTERN << 4));

                // Double buffer only by Vsync
                ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT1);

                // Phy Input Data from Tx Mac (SST)
                ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

                break;

            default:
                break;
        }
    }

    // Play audio if get audio packet or replay audio if channel count is changed
    if((GET_DP_TX_AUDIO_READY_TO_PLAY() == _TRUE) && ((ScalerDpTxAudioGetSamplingFreqRange() != GET_DP_TX_CURRENT_AUDIO_FREQUENCY()) || (ScalerDpTxAudioGetChannelChange() == _TRUE)))
    {
        if(ScalerDpTxAudioGetSamplingFreqRange() != _DP_TX_AUDIO_FREQ_NO_AUDIO)
        {
            ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_ON);
        }
        else
        {
            ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_STANDBY);
        }

        SET_DP_TX_CURRENT_AUDIO_FREQUENCY(ScalerDpTxAudioGetSamplingFreqRange());
    }
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSetStreamSource(EnumDPTxInputSource enumStreamSource)
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
}

//--------------------------------------------------
// Description  : Set DP Tx Stream Source for EXINT
// Input Value  : EnumDPTxInputSource
// Output Value : None
//--------------------------------------------------
void ScalerDpTxSetStreamSource_EXINT0(EnumDPTxInputSource enumStreamSource) using 1
{
    SET_DP_TX_STREAM_SOURCE(enumStreamSource);
    SET_DP_TX_STREAM_SOURCE_CHANGE();

    if(enumStreamSource == _DP_TX_SOURCE_NONE)
    {
        // Clear Exceed BW Flag for Clone Mode
        CLR_DP_TX_EXCEED_LINK_BANDWIDTH();
    }
}

//--------------------------------------------------
// Description  : DP Tx MAC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSTSetting(void)
{
    PDATA_DWORD(0) = 0;
    PDATA_DWORD(1) = 0x8000;
    PDATA_DWORD(2) = 0;

    // Mvid = Stream clk x Nvid / Link clk
    PDATA_DWORD(0) = (DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * PDATA_DWORD(1);
    PDATA_DWORD(0) /= ((GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() == _TRUE) ? ((DWORD)270 * GET_DP_TX_DOWNSTREAM_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DP_TX_DOWNSTREAM_LINK_RATE()));

    // Debounce 10 times
    pData[12] = 0x0A;

    do
    {
        // Select HW mode for Mvid
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);

        ScalerTimerDelayXms(2);

        // Select HW mode for Mvid
        ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

        // Get Mvid From HW Mode
        PDATA_DWORD(2) = (((DWORD)ScalerGetByte(PBB_AF_MVID_AUTO_H) << 16) | ((DWORD)ScalerGetByte(PBB_B0_MVID_AUTO_M) << 8) | ScalerGetByte(PBB_B1_MVID_AUTO_L));

        // For RLE0779A/RL6449A disable auto Mvid is zero
        if(PDATA_DWORD(2) == 0)
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            ScalerSetByte(PBB_A9_MN_M_VID_H, pData[1]);
            ScalerSetByte(PBB_AA_MN_M_VID_M, pData[2]);
            ScalerSetByte(PBB_AB_MN_M_VID_L, pData[3]);

            break;
        }

        if(abs(PDATA_DWORD(0) - PDATA_DWORD(2)) < (PDATA_DWORD(0) >> 1))
        {
            // Set Mvid for HW mode
            ScalerSetByte(PBB_A9_MN_M_VID_H, pData[9]);
            ScalerSetByte(PBB_AA_MN_M_VID_M, pData[10]);
            ScalerSetByte(PBB_AB_MN_M_VID_L, pData[11]);

            break;
        }

        pData[12]--;

        if(pData[12] == 0x00)
        {
            // HW Auto Mvid is wrong Set Mvid for FW mode
            ScalerSetByte(PBB_A9_MN_M_VID_H, pData[1]);
            ScalerSetByte(PBB_AA_MN_M_VID_M, pData[2]);
            ScalerSetByte(PBB_AB_MN_M_VID_L, pData[3]);
        }
    }
    while(pData[12] != 0);

    // Set Nvid for FW mode
    ScalerSetByte(PBB_AC_MN_N_VID_H, pData[5]);
    ScalerSetByte(PBB_AD_MN_N_VID_M, pData[6]);
    ScalerSetByte(PBB_AE_MN_N_VID_L, pData[7]);

    // Set Mvid DB Direct Effective
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT6, 0x00);

    // Set Mvid DB for FW mode
    ScalerSetBit(PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

    // For Mvid Auto New Mode, M/N mode Measure and Generate are Independant.
    // SET_DP_TX_MVID_FW_MODE -> FW Manually Set Mvid/Nvid
    SET_DP_TX_MVID_FW_MODE();

    // MSA fill
    ScalerDpTxSSTMSASetting();

    // DP Tx TU Setting
    ScalerDpTxSSTDisplayFormatSetting();

    // Clear FIFO Status
    ScalerSetByte(PBB_A4_PG_FIFO_CTRL, 0xFF);

    // Set up Audio Output
    ScalerDpTxSSTAudioPlaySetting(_DP_TX_AUDIO_PRESET);
}

//--------------------------------------------------
// Description  : DP Tx Set Audio Channel Count
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
void ScalerDpTxAudioSetting(void)
{
    BYTE ucPacketPerSample = 0;
    WORD usMaxAudioPacket = 0;
    WORD usBe2Be = 0;

    if(GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST)
    {
        SET_DP_TX_AUDIO_CHANNEL_COUNT(ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4);

        if(GET_DP_TX_AUDIO_CHANNEL_COUNT() > _AUDIO_CHANNEL_COUNT_2)
        {
            // Set 8 channel layout and audio source from MST
            ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // Set Audio Packet Per Sample
            ucPacketPerSample = 40;
        }
        else
        {
            // Set 2 channel layout and audio source from MST
            ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), _BIT7);

            // Set Audio Packet Per Sample
            ucPacketPerSample = 20;
        }
    }
    else
    {
        SET_DP_TX_AUDIO_CHANNEL_COUNT(_AUDIO_CHANNEL_COUNT_2);

        // Set 2 channel layout and audio source from I2S
        ScalerSetBit(PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), 0x00);

        // Set Audio Packet Per Sample
        ucPacketPerSample = 20;
    }

    // sec_end_cnt = max_audio_packet (lane_num, max_long_packet_cnt) + safe_margin
    // max_audio_packet = SS&SE + HEADER&ECC BYTES / lane_num + [(max_long_packet_cnt+1) * (minimum packet payload + 4)] / lane_num.
    usMaxAudioPacket = 2 + ((8 + ucPacketPerSample) / GET_DP_TX_DOWNSTREAM_LANE_NUM());

    // Get BE2BE Period with Htotal
    usBe2Be = (DWORD)g_stDPTxInputTimingInfo.usHTotal * 270 * GET_DP_TX_DOWNSTREAM_LINK_RATE() / GET_DP_TX_INPUT_PIXEL_CLK();

    // Get 70% of blanking period
    usBe2Be = (DWORD)(usBe2Be - GET_DP_TX_HORIZONTAL_DE_PERIOD()) * 7 / 10;

    // if BS2BE > max_audio_packet, Sec_end_count = BS2BE - max_audio_packet
    // else Sec_end_count = 0;
    if(usBe2Be > usMaxAudioPacket)
    {
        // Set Seccondary End Count
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, HIBYTE(usBe2Be - usMaxAudioPacket));
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, LOBYTE(usBe2Be - usMaxAudioPacket));
    }
    else
    {
        // Set Seccondary End Count
        ScalerSetByte(PBB_D4_ARBITER_SEC_END_CNT_HB, 0x00);
        ScalerSetByte(PBB_D5_ARBITER_SEC_END_CNT_LB, 0x00);
    }
}

//--------------------------------------------------
// Description  : Get Audio Channel Count Change For MST2SST
// Input Value  :
// Output Value : Changed => _TRUE or No Changed => _FALSE
//--------------------------------------------------
bit ScalerDpTxAudioGetChannelChange(void)
{
    // Get Channel Count from DP Source
    if((ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT6 | _BIT5 | _BIT4)) >> 4) > _AUDIO_CHANNEL_COUNT_2)
    {
        // Campare 8 channel count with DP TX audio
        return (ScalerGetBit(PBC_18_AUD_FUNCTION_CTRL1, _BIT6) == _BIT6) ? _FALSE : _TRUE;
    }
    else
    {
        // Campare 2 channel count with DP TX audio
        return (ScalerGetBit(PBC_18_AUD_FUNCTION_CTRL1, _BIT6) == 0x00) ? _FALSE : _TRUE;
    }
}

//--------------------------------------------------
// Description  : DP Tx Get Audio Sampling Frequency Packet
// Input Value  :
// Output Value : Packet Number
//--------------------------------------------------
WORD ScalerDpTxAudioGetSamplingFreqPacket(void)
{
    switch(ScalerDpTxAudioGetSamplingFreqRange())
    {
        case _DP_TX_AUDIO_FREQ_32K:

            return 320;

        case _DP_TX_AUDIO_FREQ_44_1K:

            return 441;

        case _DP_TX_AUDIO_FREQ_48K:

            return 480;

        case _DP_TX_AUDIO_FREQ_64K:

            return 640;

        case _DP_TX_AUDIO_FREQ_88_2K:

            return 882;

        case _DP_TX_AUDIO_FREQ_96K:

            return 960;

        case _DP_TX_AUDIO_FREQ_128K:

            return 1280;

        case _DP_TX_AUDIO_FREQ_176_4K:

            return 1764;

        case _DP_TX_AUDIO_FREQ_192K:

            return 1920;

        case _DP_TX_AUDIO_FREQ_256K:

            return 2560;

        case _DP_TX_AUDIO_FREQ_352_8K:

            return 3528;

        case _DP_TX_AUDIO_FREQ_384K:

            return 3840;

        case _DP_TX_AUDIO_FREQ_512K:

            return 5120;

        case _DP_TX_AUDIO_FREQ_705_6K:

            return 7056;

        case _DP_TX_AUDIO_FREQ_768K:

            return 7680;

        case _DP_TX_AUDIO_FREQ_NO_AUDIO:
        default:

            return 0;
    }
}

//--------------------------------------------------
// Description  : DP Tx Set Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpTxSetSecDataHeader(EnumDPTxSecDataPacketType enumPackettype)
{
    BYTE pucData[4];

    memset(pucData, 0, sizeof(pucData));

    // Sec Data Packet ID
    pucData[0] = 0x00;

    // Packet Type
    pucData[1] = enumPackettype;

    // Select Packet Type
    ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[1]);

    switch(enumPackettype)
    {
        case _SEC_PACKET_TYPE_AUDIO_TIMESTAMP:

            // Audio Timestamp LSB of (Data Byte count - 1)
            pucData[2] = 0x17;

            // [1:0]: Audio Timestamp MSB of (Data Byte count - 1), [7:2] DP version number
            pucData[3] = (_DP_VERSION_1_1 << 2);

            break;

        case _SEC_PACKET_TYPE_AUDIO_STREAM:

            // Reserved
            pucData[2] = 0x00;

            // [7:4]: Codeing type
            pucData[3] = (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST2SST) ? ScalerGetBit(PBC_4A_MST_SEC_PKT_HB3, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) : 0x00;

            // [2:0]: Channel count
            pucData[3] = (pucData[3] << 4) | GET_DP_TX_AUDIO_CHANNEL_COUNT();

            break;

        case _SEC_PACKET_TYPE_VSC:

            // [4:0]: Revision number
            pucData[2] = 0x01;

            // [4:0]: Number of valid data bytes
            pucData[3] = 0x01;

            break;

        case _SEC_PACKET_TYPE_INFOFRAME_AVI:
        case _SEC_PACKET_TYPE_INFOFRAME_AUDIO:
        case _SEC_PACKET_TYPE_INFOFRAME_MPEG:

            // Set CEA-861 InfoFrame
            pucData[1] = _BIT7 | (pucData[1] & 0x07);

            // LSB of (Data Byte count - 1)
            pucData[2] = 0x1B;

            // [1:0]: MSB of (Data Byte count - 1), [7:2] DP version number
            pucData[3] = (_DP_VERSION_1_1 << 2);

            break;

        case _SEC_PACKET_TYPE_INFOFRAME_RSV:

            // DP AMD SPD Info
            pucData[1] = 0x83;

            // DP AMD SPD Info
            pucData[2] = 0x01;

            // DP AMD SPD Info
            pucData[3] = 0x08;

            break;

        default:
            break;
    }

    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, pucData[0]);
    ScalerSetByte(PBC_74_SEC_PH_HB1, pucData[1]);
    ScalerSetByte(PBC_75_SEC_PH_HB2, pucData[2]);
    ScalerSetByte(PBC_76_SEC_PH_HB3, pucData[3]);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, ScalerDpTxAudioGetSecDataParity(pucData[0]));
    ScalerSetByte(PBC_78_SEC_PH_PB1, ScalerDpTxAudioGetSecDataParity(pucData[1]));
    ScalerSetByte(PBC_79_SEC_PH_PB2, ScalerDpTxAudioGetSecDataParity(pucData[2]));
    ScalerSetByte(PBC_7A_SEC_PH_PB3, ScalerDpTxAudioGetSecDataParity(pucData[3]));

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP Tx Clear Header byte for Sec Data
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
void ScalerDpTxClearSecDataHeader(EnumDPTxSecDataPacketType enumPackettype)
{
    // Select Packet Type
    ScalerSetBit(PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), enumPackettype);

    // Set Header Byte
    ScalerSetByte(PBC_73_SEC_PH_HB0, 0x00);
    ScalerSetByte(PBC_74_SEC_PH_HB1, 0x00);
    ScalerSetByte(PBC_75_SEC_PH_HB2, 0x00);
    ScalerSetByte(PBC_76_SEC_PH_HB3, 0x00);

    // Set Parity Byte
    ScalerSetByte(PBC_77_SEC_PH_PB0, 0x00);
    ScalerSetByte(PBC_78_SEC_PH_PB1, 0x00);
    ScalerSetByte(PBC_79_SEC_PH_PB2, 0x00);
    ScalerSetByte(PBC_7A_SEC_PH_PB3, 0x00);

    // Set Double Buffer
    ScalerSetBit(PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : DP Tx Get Parity byte for Audio Packet Header
// Input Value  : Packet Header
// Output Value : Packet Parity
//--------------------------------------------------
BYTE ScalerDpTxAudioGetSecDataParity(BYTE ucHeader)
{
    BYTE ucParity = 0;

    // Bit 7
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 7;

    // Bit 6
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader))) << 6;

    // Bit 5
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 5;

    // Bit 4
    ucParity |= ((BYTE)(GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 4;

    // Bit 3
    ucParity |= ((BYTE)(GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT6(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 3;

    // Bit 2
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT6(ucHeader))) << 2;

    // Bit 1
    ucParity |= ((BYTE)(GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT1(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT5(ucHeader) ^ GET_DATA_BIT7(ucHeader))) << 1;

    // Bit 0
    ucParity |= (GET_DATA_BIT0(ucHeader) ^ GET_DATA_BIT2(ucHeader) ^ GET_DATA_BIT3(ucHeader) ^ GET_DATA_BIT4(ucHeader) ^ GET_DATA_BIT7(ucHeader));

    return ucParity;
}

//--------------------------------------------------
// Description  : DP Tx Arbiter
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSTDisplayFormatSetting(void)
{
    // Disable HW Auto Calculate H Delay
    ScalerSetBit(PBB_D3_LFIFO_WL_SET, ~_BIT7, 0x00);

    // Pixel Generation Block Reset
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT7, 0x00);

    // Set Interlace Bit of VBID as Interlace Mode Detected
    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT0, _BIT0);
    }
    else
    {
        ScalerSetBit(PBB_C7_VBID, ~_BIT0, 0x00);
    }

    // Get Bit Per Chrome
    switch(GET_DP_TX_INPUT_COLOR_DEPTH())
    {
        case 0x00:
            pData[0] = 6;
            break;

        case 0x01:
            pData[0] = 8;
            break;

        case 0x02:
            pData[0] = 10;
            break;

        case 0x03:
            pData[0] = 12;
            break;

        case 0x04:
            pData[0] = 16;
            break;

        default:

            pData[0] = 8;
            break;
    }

    pData[1] = ((GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422) ? 2 : (GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY) ? 1 : 3);

    // step1: Cal vaild symbol in TU
    // Average TU = TU Size x (Stream_Clk x Byte of 1 pixel / Lane Number) / Link Rate
    PDATA_WORD(1) = ((GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() == _TRUE) ? ((DWORD)270 * GET_DP_TX_DOWNSTREAM_LINK_RATE() * 9975 / 10000) : ((DWORD)270 * GET_DP_TX_DOWNSTREAM_LINK_RATE()));
    PDATA_WORD(1) = ((DWORD)_DP_TX_SST_TU_SIZE * (((DWORD)GET_DP_TX_INPUT_PIXEL_CLK() * pData[1] * pData[0]) / GET_DP_TX_DOWNSTREAM_LANE_NUM())) / (PDATA_WORD(1));

    ScalerSetByte(PBB_CC_TU_SIZE, _DP_TX_SST_TU_SIZE);
    ScalerSetByte(PBB_CD_TU_DATA_SIZE0, (PDATA_WORD(1) >> 3));
    ScalerSetByte(PBB_CE_TU_DATA_SIZE1, (PDATA_WORD(1) & 0x07));

    PDATA_WORD(2) = ((DWORD)g_stDPTxInputTimingInfo.usHWidth * pData[0] * pData[1]) / (GET_DP_TX_DOWNSTREAM_LANE_NUM() * 8);
    PDATA_WORD(2) += ((bit)(((DWORD)g_stDPTxInputTimingInfo.usHWidth * pData[0] * pData[1]) % (GET_DP_TX_DOWNSTREAM_LANE_NUM() * 8)) ? 1 : 0);

    ScalerSetByte(PBB_CA_V_DATA_PER_LINE0, pData[4]);
    ScalerSetByte(PBB_CB_V_DATA_PER_LINE1, pData[5]);

    // Get TU Number Per Line
    PDATA_WORD(0) = (PDATA_WORD(2) << 3) / PDATA_WORD(1) + (((PDATA_WORD(2) << 3) % PDATA_WORD(1) > 0) ? 1 : 0);

    // Store Horizontal DE for Sec Data End Count
    SET_DP_TX_HORIZONTAL_DE_PERIOD(PDATA_WORD(0) * _DP_TX_SST_TU_SIZE);

    // step 3: Enable HW Auto Calculate H Delay
    ScalerSetBit(PBB_D3_LFIFO_WL_SET, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : DP Tx MSA Generation
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSTMSASetting(void)
{
    // Reset MSA Generation Block and SEC Block
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
    ScalerSetBit(PBB_A1_DP_RESET_CTRL, ~_BIT6, 0x00);

    // Set Htotal
    ScalerSetByte(PBB_B7_MN_STRM_ATTR_HTT_M, HIBYTE(g_stDPTxInputTimingInfo.usHTotal));
    ScalerSetByte(PBB_B8_MN_STRM_ATTR_HTT_L, LOBYTE(g_stDPTxInputTimingInfo.usHTotal));

    // Set Hstart
    ScalerSetByte(PBB_B9_MN_STRM_ATTR_HST_M, HIBYTE(g_stDPTxInputTimingInfo.usHStart));
    ScalerSetByte(PBB_BA_MN_STRM_ATTR_HST_L, LOBYTE(g_stDPTxInputTimingInfo.usHStart));

    // Set Hwidth
    ScalerSetByte(PBB_BB_MN_STRM_ATTR_HWD_M, HIBYTE(g_stDPTxInputTimingInfo.usHWidth));
    ScalerSetByte(PBB_BC_MN_STRM_ATTR_HWD_L, LOBYTE(g_stDPTxInputTimingInfo.usHWidth));

    // Set Hsyc
    ScalerSetByte(PBB_BD_MN_STRM_ATTR_HSW_M, HIBYTE(g_stDPTxInputTimingInfo.usHSWidth));
    ScalerSetByte(PBB_BE_MN_STRM_ATTR_HSW_L, LOBYTE(g_stDPTxInputTimingInfo.usHSWidth));

    // Set Vtotal
    ScalerSetByte(PBB_BF_MN_STRM_ATTR_VTTE_M, HIBYTE(g_stDPTxInputTimingInfo.usVTotal));
    ScalerSetByte(PBB_C0_MN_STRM_ATTR_VTTE_L, LOBYTE(g_stDPTxInputTimingInfo.usVTotal));

    // Set VStart
    ScalerSetByte(PBB_C1_MN_STRM_ATTR_VST_M, HIBYTE(g_stDPTxInputTimingInfo.usVStart));
    ScalerSetByte(PBB_C2_MN_STRM_ATTR_VST_L, LOBYTE(g_stDPTxInputTimingInfo.usVStart));

    // Set VHeight
    ScalerSetByte(PBB_C3_MN_STRM_ATTR_VHT_M, HIBYTE(g_stDPTxInputTimingInfo.usVHeight));
    ScalerSetByte(PBB_C4_MN_STRM_ATTR_VHT_L, LOBYTE(g_stDPTxInputTimingInfo.usVHeight));

    // Set Vsync
    ScalerSetByte(PBB_C5_MN_STRM_ATTR_VSW_M, HIBYTE(g_stDPTxInputTimingInfo.usVSWidth));
    ScalerSetByte(PBB_C6_MN_STRM_ATTR_VSW_L, LOBYTE(g_stDPTxInputTimingInfo.usVSWidth));

    // Set Color Space
    switch(GET_DP_TX_INPUT_COLOR_SPACE())
    {
        case _COLOR_SPACE_YCBCR422:

            // Set Color depth and YCbCr 422 Mode
            ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), ((BYTE)(GET_DP_TX_INPUT_COLOR_DEPTH() << 5) | _BIT1));

            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT7, 0x00);

            break;

        case _COLOR_SPACE_YCBCR444:

            // Set Color depth and YCbCr 444 Mode
            ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), ((BYTE)(GET_DP_TX_INPUT_COLOR_DEPTH() << 5) | _BIT2));

            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT7, 0x00);

            break;

        case _COLOR_SPACE_Y_ONLY:

            ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), (((BYTE)GET_DP_TX_INPUT_COLOR_DEPTH() << 5) | (_BIT2 | _BIT1)));

            // Set Y Only Mode
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT7, _BIT7);

            break;

        case _COLOR_SPACE_RGB:
        default:

            // Set Color depth and RGB Mode
            ScalerSetBit(PBB_B5_MSA_MISC0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT2 | _BIT1), ((BYTE)GET_DP_TX_INPUT_COLOR_DEPTH() << 5));

            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT7, 0x00);

            break;
    }

    DebugMessageMst("DP Tx MSA Color Space 1", GET_DP_TX_INPUT_COLOR_SPACE());

    // MSA_DB = 1
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);

    if(GET_DP_TX_INPUT_INTERLACE_MODE() == _ON)
    {
        // Set MISC1
        if(GET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER() == _EVEN)
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, _BIT0);
        }
        else
        {
            ScalerSetBit(PBB_B6_MN_STRM_ATTR_MISC1, ~_BIT0, 0x00);
        }
    }

    // MSA_DB = 1
    ScalerSetBit(PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);

    DebugMessageMst("DP Tx MSA Color Space 2", ScalerGetBit(PBB_B5_MSA_MISC0, (_BIT2 | _BIT1)));
}

//--------------------------------------------------
// Description  : DP Tx Link Training
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxLinkTraining(void)
{
    if(GET_DP_TX_CTS_TEST_REQUEST_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING) == _DP_TX_CTS_TEST_LINK_TRAINING)
    {
        // Read TEST_LINK_RATE
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x19, 1, pData);

        SET_DP_TX_DOWNSTREAM_MAX_LINK_RATE(pData[0]);

        // Read TEST_LANE_COUNT
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x20, 1, pData);

        SET_DP_TX_DOWNSTREAM_LANE_NUM((pData[0] & 0x1F));

        CLR_DP_TX_CTS_TEST_REQUEST_TARGET_TYPE(_DP_TX_CTS_TEST_LINK_TRAINING);
    }
    else
    {
        // Power Up Downstream
        pData[0] = 0x01;
        ScalerDpTxAuxNativeWrite(0x00, 0x06, 0x00, 1, pData);

        // Read Lane0/Lane1/Lane2/Lane3 CR_DONE/EQ_DONE/Symbol Locked/Lane Align
        ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 3, pData);

        if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && (pData[0] == 0x77) && (pData[1] == 0x77) && ((pData[2] & _BIT0) == _BIT0)) ||
           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && (pData[0] == 0x77) && ((pData[2] & _BIT0) == _BIT0)) ||
           ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (pData[0] == 0x07)))
        {
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
            return;
        }
    }

    ScalerDpTxTPInitialSet();

    while((GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS) && (GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_FAIL))
    {
        switch(GET_DP_TX_LT_STATE())
        {
            case _DP_TX_TRAINING_PATTERN1:

                SET_DP_TX_LT_RESULT(ScalerDpTxTrainPattern1());

                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
                {
                    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN2);
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
                {
                    if(ScalerDpTxLinkRateReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                    {
                        if(ScalerDpTxLaneCountReduce(_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL) == _FAIL)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                    }
                }

                break;

            case _DP_TX_TRAINING_PATTERN2:

                SET_DP_TX_LT_RESULT(ScalerDpTxTrainPattern2());

                if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_PASS)
                {
                    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                }
                else if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
                {
                    if(ScalerDpTxLaneCountReduce(_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL) == _FAIL)
                    {
                        if(ScalerDpTxLinkRateReduce(_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL) == _FAIL)
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
                        }
                        else
                        {
                            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                        }
                    }
                    else
                    {
                        SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);
                        SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
                    }
                }

                break;

            case _DP_TX_TRAINING_PATTERN_END:

                if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PATTERN2_PASS)
                {
                    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);
                }
                else
                {
                    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_PASS);
                }

                ScalerDpTxTrainPatternEnd();

                break;

            default:

                break;
        }

        if(GET_DP_TX_HPD_STATUS_CHANGE() == _TRUE)
        {
            SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_FAIL);

            SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN_END);
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Inital Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTPInitialSet(void)
{
    SET_DP_TX_LT_RESULT(_DP_TX_TRAINING_NO_RESULT);
    SET_DP_TX_LT_STATE(_DP_TX_TRAINING_PATTERN1);

    SET_DP_TX_DOWNSTREAM_LINK_RATE(GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());
    SET_DP_TX_DOWNSTREAM_LANE_NUM(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM());
    SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM());

    // Set Analog PHY CMU to gen Link Rate
    ScalerGDIPhyTxCMUPowerOn();

    // Initialize Main Link Signal
    ScalerDpTxSignalInitialSetting();

    ScalerDpTxAuxNativeRead(0x00, 0x01, 0x07, 1, pData);

    // Set Down Spread
    pData[0] = ((pData[0] & ~_BIT4) | ((BYTE)GET_DP_TX_DOWNSTREAM_DOWN_SPREAD() << 4));
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x07, 1, pData);

    // Set Link Rate
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 1, &GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());

    // Set Link Count and Enhance Framing
    pData[0] = ((BYTE)GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | GET_DP_TX_DOWNSTREAM_LANE_NUM();
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x01, 1, pData);
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpTxTrainPattern1(void)
{
    // Start TP1 Process
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_NO_RESULT)
    {
        // Main Link switch to TP1 Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_TPS1 << 4));
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        pData[0] = _DP_TP_1 | _DP_SCRAMBLING_DISABLE;
        pData[1] = g_stTxLTInfo.ucLane0Adjust;
        pData[2] = g_stTxLTInfo.ucLane1Adjust;
        pData[3] = g_stTxLTInfo.ucLane2Adjust;
        pData[4] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h to Start TP1
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerGDIPhyTxMLPHYSet();

        pData[0] = g_stTxLTInfo.ucLane0Adjust;
        pData[1] = g_stTxLTInfo.ucLane1Adjust;
        pData[2] = g_stTxLTInfo.ucLane2Adjust;
        pData[3] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= 0x12)
    {
        // Read Training Aux Read Interval
        ScalerDpTxAuxNativeRead(0x00, 0x00, 0x0E, 1, pData);

        pData[0] &= 0x7F;

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4*pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Read Lane Status and Request Adjust Level
    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 6, pData);
    g_stTxLTInfo.ucLane01LTStatus = pData[0];
    g_stTxLTInfo.ucLane23LTStatus = pData[1];
    g_stTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stTxLTInfo.ucAdjustReqLane23 = pData[5];

    if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DP_TX_LANE3_CR_DONE() & GET_DP_TX_LANE2_CR_DONE() & GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && ((GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) == _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (GET_DP_TX_LANE0_CR_DONE() == _TRUE)))
    {
        return _DP_TX_TRAINING_PATTERN1_PASS;
    }

    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            if(ScalerDpTxTP1Lane3Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane2Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_TWO_LANE:

            if(ScalerDpTxTP1Lane1Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;

        case _DP_ONE_LANE:
        default:

            if(ScalerDpTxTP1Lane0Adjust() == _FAIL)
            {
                return _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL;
            }

            break;
    }

    return _DP_TX_TRAINING_PATTERN1_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane0 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane0Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE0_ADJUST_VOL_SWING() + GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == GET_DP_TX_LANE0_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE0_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE0_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE0_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane1 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane1Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE1_ADJUST_VOL_SWING() + GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == GET_DP_TX_LANE1_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE1_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE1_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE1_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane2 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane2Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE2_ADJUST_VOL_SWING() + GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == GET_DP_TX_LANE2_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE2_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE2_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE2_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 1 Lane3 Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxTP1Lane3Adjust(void)
{
    // Check1: (Adjust Vol swing level + Current Vol pre emphasisl) > 3
    if((GET_DP_TX_LANE3_ADJUST_VOL_SWING() + GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_VOL_SWING((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS()));
    }

    // Check2: Current Vol swing level is the same as adjust Vol swing level
    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == GET_DP_TX_LANE3_ADJUST_VOL_SWING())
    {
        ADD_DP_TX_TP1_LANE3_SAME_VOL_CNT();

        if((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 5) || ((GET_DP_TX_TP1_LANE3_SAME_VOL_CNT() == 1) && (GET_DP_TX_LANE3_ADJUST_VOL_SWING() == _DP_TX_LEVEL_3)))
        {
            CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

            return _FAIL;
        }
    }
    else
    {
        CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();
    }

    // Set Tx Current voltage swing based on Rx Adjust voltage(flag)
    SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2
// Input Value  :
// Output Value :
//--------------------------------------------------
BYTE ScalerDpTxTrainPattern2(void)
{
    // Start TP2 Process
    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PATTERN1_PASS)
    {
        // Check TP3 Supported
        if(GET_DP_TX_DOWNSTREAM_TP3_SUPPORT() == _TRUE)
        {
            // Main Link Switch to TPS3 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_TPS3 << 4));
            pData[0] = _DP_TP_3;
        }
        else
        {
            // Main Link Switch to TPS2 Pattern
            ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_TPS2 << 4));
            pData[0] = _DP_TP_2;
        }

        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Disable Scrambling
        pData[0] |= _DP_SCRAMBLING_DISABLE;
        pData[1] = g_stTxLTInfo.ucLane0Adjust;
        pData[2] = g_stTxLTInfo.ucLane1Adjust;
        pData[3] = g_stTxLTInfo.ucLane2Adjust;
        pData[4] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 102h-107h to Start TP2
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 5, pData);
    }
    else
    {
        // Set Output Signal According to Request
        ScalerGDIPhyTxMLPHYSet();

        pData[0] = g_stTxLTInfo.ucLane0Adjust;
        pData[1] = g_stTxLTInfo.ucLane1Adjust;
        pData[2] = g_stTxLTInfo.ucLane2Adjust;
        pData[3] = g_stTxLTInfo.ucLane3Adjust;

        // Write DPCD 103h-107h (Voltage Swing and Pre-emphasis)
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x03, 4, pData);
    }

    if(GET_DP_TX_DOWNSTREAM_DPCD_REV() >= 0x12)
    {
        pData[0] = (_DP_LANE0_MAX_POST_CURSOR2_REACHED | _DP_LANE1_MAX_POST_CURSOR2_REACHED);
        pData[1] = (_DP_LANE2_MAX_POST_CURSOR2_REACHED | _DP_LANE3_MAX_POST_CURSOR2_REACHED);
        ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x0F, 2, pData);

        // Read Training Aux Read Interval
        ScalerDpTxAuxNativeRead(0x00, 0x00, 0x0E, 1, pData);

        if(pData[0] > 0x04)
        {
            pData[0] = 0;
        }
    }
    else
    {
        pData[0] = 0;
    }

    if(pData[0] != 0x00)
    {
        // Delay 4 * pData[0] ms
        ScalerTimerDelayXms(pData[0] << 2);
    }
    else
    {
        // Delay 400us
        for(pData[0] = 0; pData[0] < 55; pData[0]++)
        {
            Delay5us(g_ucDelay5usN);
        }
    }

    // Read Lane Status and Request Adjust Level
    ScalerDpTxAuxNativeRead(0x00, 0x02, 0x02, 6, pData);
    g_stTxLTInfo.ucLane01LTStatus = pData[0];
    g_stTxLTInfo.ucLane23LTStatus = pData[1];
    g_stTxLTInfo.ucLaneAlignStatus = pData[2];
    g_stTxLTInfo.ucAdjustReqLane01 = pData[4];
    g_stTxLTInfo.ucAdjustReqLane23 = pData[5];

    // CDR unlock => Reduce bit rate and return to TP1
    if(((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DP_TX_LANE3_CR_DONE() & GET_DP_TX_LANE2_CR_DONE() & GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && ((GET_DP_TX_LANE1_CR_DONE() & GET_DP_TX_LANE0_CR_DONE()) != _TRUE)) ||
       ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (GET_DP_TX_LANE0_CR_DONE() != _TRUE)))
    {
        CLR_DP_TX_TP2_CNT();

        return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }

    if((((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_FOUR_LANE) && ((GET_DP_TX_LANE3_EQ_DONE() & GET_DP_TX_LANE2_EQ_DONE() & GET_DP_TX_LANE1_EQ_DONE() & GET_DP_TX_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_TWO_LANE) && ((GET_DP_TX_LANE1_EQ_DONE() & GET_DP_TX_LANE0_EQ_DONE()) == _TRUE)) ||
        ((GET_DP_TX_DOWNSTREAM_LANE_NUM() == _DP_ONE_LANE) && (GET_DP_TX_LANE0_EQ_DONE() == _TRUE))) &&
       (GET_DP_TX_LANE_ALIGN_DONE() == _TRUE))
    {
        CLR_DP_TX_TP2_CNT();

        return _DP_TX_TRAINING_PATTERN2_PASS;
    }

    if(GET_DP_TX_TP2_CNT() >= 5)
    {
        CLR_DP_TX_TP2_CNT();

        return _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL;
    }
    else
    {
        ADD_DP_TX_TP2_CNT();
    }

    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            ScalerDpTxTP2Lane3Adjust();
            ScalerDpTxTP2Lane2Adjust();
            ScalerDpTxTP2Lane1Adjust();
            ScalerDpTxTP2Lane0Adjust();

            break;

        case _DP_TWO_LANE:

            ScalerDpTxTP2Lane1Adjust();
            ScalerDpTxTP2Lane0Adjust();

            break;

        case _DP_ONE_LANE:
        default:

            ScalerDpTxTP2Lane0Adjust();

            break;
    }

    return _DP_TX_TRAINING_PATTERN2_FAIL;
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane0  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane0Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE0_CURRENT_VOL_SWING() + GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE0_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE0_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE0_CURRENT_VOL_SWING(GET_DP_TX_LANE0_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE0_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane1  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane1Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE1_CURRENT_VOL_SWING() + GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE1_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE1_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE1_CURRENT_VOL_SWING(GET_DP_TX_LANE1_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE1_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane2  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane2Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE2_CURRENT_VOL_SWING() + GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE2_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE2_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE2_CURRENT_VOL_SWING(GET_DP_TX_LANE2_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE2_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training 2 Lane3  Adjust
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTP2Lane3Adjust(void)
{
    // Check: (Current Vol swing level + Adjust Vol swing level) > 3
    if((GET_DP_TX_LANE3_CURRENT_VOL_SWING() + GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS()) > _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS((_DP_TX_LEVEL_3 - GET_DP_TX_LANE3_CURRENT_VOL_SWING()));
    }
    else
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(GET_DP_TX_LANE3_ADJUST_PRE_EMPHASIS());
        SET_DP_TX_LANE3_CURRENT_VOL_SWING(GET_DP_TX_LANE3_ADJUST_VOL_SWING());
    }

    if(GET_DP_TX_LANE3_CURRENT_VOL_SWING() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    }

    if(GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS() == _DP_TX_LEVEL_3)
    {
        SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
    else
    {
        CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxLinkRateReduce(EnumDPTxLTResult enumDPTxLTResult)
{
    switch(GET_DP_TX_DOWNSTREAM_LINK_RATE())
    {
        case _DP_LINK_HBR2:

            SET_DP_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_HBR);

            if(enumDPTxLTResult == _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
            {
                SET_DP_TX_DOWNSTREAM_LANE_NUM(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP());
            }

            pData[0] = _DP_LINK_HBR;
            pData[1] = ((GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | GET_DP_TX_DOWNSTREAM_LANE_NUM());

            // Write Link Rate to DPCD 100h and Lane Count to DPCD 101h
            ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 2, pData);

            break;

        case _DP_LINK_HBR:

            SET_DP_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_RBR);

            if(enumDPTxLTResult == _DP_TX_TRAINING_PATTERN2_ADJUST_FAIL)
            {
                SET_DP_TX_DOWNSTREAM_LANE_NUM(GET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP());
            }

            pData[0] = _DP_LINK_RBR;
            pData[1] = ((GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | GET_DP_TX_DOWNSTREAM_LANE_NUM());

            // Write Link Rate to DPCD 100h and Lane Count to DPCD 101h
            ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 2, pData);

            break;

        default:

            switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
            {
                case _DP_LINK_4_LANE:

                    SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(_DP_LINK_2_LANE);
                    break;

                case _DP_LINK_2_LANE:

                    SET_DP_TX_DOWNSTREAM_MAX_LANE_NUM_TEMP(_DP_LINK_1_LANE);
                    break;

                default:
                    break;
            }

            return _FAIL;

            break;
    }

    // Tx Lane Setting
    ScalerDpTxSignalLaneSetting();

    // Change Analog PHY CMU Clk
    ScalerGDIPhyTxCMUPowerOn();

    // Reset Signal Level
    ScalerDpTxSignalReset();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Lane Count Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxLaneCountReduce(EnumDPTxLTResult enumDPTxLTResult)
{
    PDATA_WORD(0) = 0;

    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_LINK_4_LANE:

            if(enumDPTxLTResult == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
            {
                SET_DP_TX_DOWNSTREAM_LINK_RATE(GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());
            }

            SET_DP_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_2_LANE);

            pData[0] = GET_DP_TX_DOWNSTREAM_LINK_RATE();
            pData[1] = ((GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | _DP_LINK_2_LANE);

            // Write Link Rate to DPCD 100h and Lane Count to DPCD 101h
            ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 2, pData);

            break;

        case _DP_LINK_2_LANE:

            if(enumDPTxLTResult == _DP_TX_TRAINING_PATTERN1_ADJUST_FAIL)
            {
                SET_DP_TX_DOWNSTREAM_LINK_RATE(GET_DP_TX_DOWNSTREAM_MAX_LINK_RATE());
            }

            SET_DP_TX_DOWNSTREAM_LANE_NUM(_DP_LINK_1_LANE);

            pData[0] = GET_DP_TX_DOWNSTREAM_LINK_RATE();
            pData[1] = ((GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 7) | _DP_LINK_1_LANE);

            // Write Link Rate to DPCD 100h and Lane Count to DPCD 101h
            ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x00, 2, pData);

            break;

        default:

            return _FAIL;

            break;
    }

    // Tx Lane Setting
    ScalerDpTxSignalLaneSetting();

    // Change Analog PHY CMU Clk
    ScalerGDIPhyTxCMUPowerOn();

    // Reset Signal Level
    ScalerDpTxSignalReset();

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : DP Tx Link Training Pattern End
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxTrainPatternEnd(void)
{
    // Write TRAINING_PATTERN_SET = 00
    pData[0] = _DP_TP_NONE;
    ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x02, 1, pData);

    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
    {
        // Enable Sramble and Enable BS replaced by SR
        ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // Phy Input Data from Tx Mac (SST)
        ScalerSetBit(PBB_00_DP_PHY_CTRL, ~_BIT1, 0x00);

        if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
        {
            ScalerDpTxSetStreamSource(GET_DP_TX_STREAM_SOURCE());
        }
    }
    else
    {
        // Power Down ML PHY
        ScalerGDIPhyTxMLPowerOff();

        // Main Link switch to IDLE Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_DP_TX_OUTPUT_IDLE_PATTERN << 4));

        // Direct Apply Idle Pattern
        ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);
    }
}

//--------------------------------------------------
// Description  : DP Tx Link Training Link Rate Reduce
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSignalReset(void)
{
    // Set Voltage Swing and pre-emphasis Variable to level 0
    CLR_DP_TX_TP1_LANE0_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE1_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE2_SAME_VOL_CNT();
    CLR_DP_TX_TP1_LANE3_SAME_VOL_CNT();

    SET_DP_TX_LANE0_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE0_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE1_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE1_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE2_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE2_CURRENT_PRE_EMPHASIS_MAX_REACH();

    SET_DP_TX_LANE3_CURRENT_VOL_SWING(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_VOL_SWING_MAX_REACH();
    SET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS(_DP_TX_LEVEL_0);
    CLR_DP_TX_LANE3_CURRENT_PRE_EMPHASIS_MAX_REACH();

    // Clear TP2 Count
    CLR_DP_TX_TP2_CNT();

    ScalerGDIPhyTxMLPHYSet();
}

//--------------------------------------------------
// Description  : Dp Tx SSC Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSSCSet(bit bSSCEn)
{
    // Set SSC
    if(bSSCEn == _ENABLE)
    {
        PDATA_WORD(0) = (WORD)((ScalerGetBit(PBC_DD_DPTX_CMU12, 0x1F) << 4) | (ScalerGetByte(PBC_DE_DPTX_CMU13) >> 4));
        PDATA_WORD(1) = (WORD)((ScalerGetBit(PBC_DE_DPTX_CMU13, 0x0F) << 8) | ScalerGetByte(PBC_DF_DPTX_CMU14));

        // Calculate SSC Frequency = 32k
        PDATA_WORD(3) = (((_EXT_XTAL / _DP_TX_SSC_FREQ) + 2) & 0xFFFC);

        // Calculate SSC 0.5 % downspread
        PDATA_WORD(2) = ((((DWORD)PDATA_WORD(0) + 4) * 4096 + PDATA_WORD(1))) * 16 / 200 / PDATA_WORD(3);

        // Set SSC Frequency = 32k
        ScalerSetByte(PBC_E1_DPTX_CMU16, (BYTE)(PDATA_WORD(3) >> 8));
        ScalerSetByte(PBC_E2_DPTX_CMU17, (BYTE) PDATA_WORD(3));

        // Set SSC 0.5 % downspread
        ScalerSetByte(PBC_E3_DPTX_CMU18, (BYTE)(PDATA_WORD(2) >> 8));
        ScalerSetByte(PBC_E4_DPTX_CMU19, (BYTE) PDATA_WORD(2));


        // [5] 1: Enable SSC, 0: disable
        // [4] 0: 1st Order SDM, 1:2nd Order SDM
        // [3] 0: Triangular wave, 1: Square wave
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~(_BIT5 | _BIT4 | _BIT3), _BIT5);
    }
    else
    {
        // Disable SSC
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);
    }
}


//--------------------------------------------------
// Description  : Dp Tx Aux PHY Set
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxAuxPHYSet(BYTE ucMode)
{
    if(ucMode == _DP_TX_AUX_SINGLE_MODE)
    {
        // Set Aux Tx LDO = 1.05V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

        // Enable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

        // Enable Enlarge Z0-N and Set ADJR-N = 0
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT4);
    }
    else
    {
#if(_AUX_TALK_MODE_LDO_VOL_TYPE == _AUX_LDO_VOL_GEN_0)
        // Set Aux Tx LDO = 0.9V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
#elif(_AUX_TALK_MODE_LDO_VOL_TYPE == _AUX_LDO_VOL_GEN_1)
        // Set Aux Tx LDO = 1.2V
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));
#endif
        // Set ADJR P
        ScalerSetBit(PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Disable Single End Mode and Enlarge Z0-P
        ScalerSetBit(PBD_62_AUX_2, ~(_BIT5 | _BIT0), _BIT0);

        // Disable Enlarge Z0-N and Set ADJR N
        ScalerSetBit(PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT1 | _BIT0));
    }

    // Set TX ADJR-P and ADJR-N
    ScalerSetByte(PBD_67_DIG_TX_03, 0xFF);
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSignalInitialSetting(void)
{
    // Set Voltage Swing and pre-emphasis level 0
    ScalerDpTxSignalReset();

    // Disable scramble
    ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT0, 0x00);

    // Set Z0 to 50 ohm
    ScalerSetByte(PBC_C2_DPTX_Z0_LANE3_2, 0x88);
    ScalerSetByte(PBC_C3_DPTX_Z0_LANE1_0, 0x88);

    // Set Lane Swap
    ScalerSetByte(PBC_AA_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Enable DP Tx
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT7 | _BIT4), (_BIT7 | _BIT4));

    // set ENHANCED Mode
    ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~_BIT2, (GET_DP_TX_DOWNSTREAM_ENHANCE_FRAMING() << 2));

    // SSC bug of PI for RLE0638
    ScalerDpTxSSCSet(_DISABLE);

    // DPTX power on TX driver and Enable output
    ScalerDpTxSignalLaneSetting();
}

//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxSignalLaneSetting(void)
{
    // DPTX power on TX driver and Enable output
    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_ONE_LANE:

            // Set Mac 1 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT0);

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

            // Disable Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, 0x00);

            // Set Daisy Chain Lane Num, 1 --> point to 1 lane
            SET_REG_DP_RX_DAISY_CHAIN_LANE_NUM(1);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

            break;

        case _DP_TWO_LANE:

            // Set Mac 2 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), _BIT1);

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3));

            // Set Daisy Chain Lane Num, 2 --> point to 2 lane
            SET_REG_DP_RX_DAISY_CHAIN_LANE_NUM(2);

            // Enable Lane Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2));
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _DP_FOUR_LANE:

            // Set Mac 4 Lane
            ScalerSetBit(PBB_A0_DP_MAC_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            // Dig PHY Set
            ScalerSetBit(PBB_00_DP_PHY_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Set Daisy Chain Lane Num, 3 --> point to 4 lane
            SET_REG_DP_RX_DAISY_CHAIN_LANE_NUM(3);

            // Enable Lane Skew
            ScalerSetBit(PBB_0D_DPTX_PHY_CTRL, ~_BIT2, _BIT2);

            // Reset Small FIFO Before Output Enable
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, 0x00);
            ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~_BIT7, _BIT7);

            ScalerSetBit(PBC_A1_DPTX_PHY_CTRL1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : On-line check for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxMeasureGetMeasureResult(StructMeasureSyncData *pstMeasureSyncHV)
{
    if(ScalerTimerPollingFlagProc(_MEASURE_TIMEOUT, P16_42_DPTX_MEAS_CTL1, _BIT7, 0x00) == _FALSE)
    {
        return _FALSE;
    }

    // Check measure result status
    if(ScalerGetBit(P16_43_DPTX_MEAS_ERROR_FLG0, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) != 0x00)
    {
        return _FALSE;
    }

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // Polarity
    pstMeasureSyncHV->b1HSP = (bit)ScalerGetBit(P16_44_DPTX_MEAS_ERROR_FLG1, _BIT6);
    pstMeasureSyncHV->b1VSP = (bit)ScalerGetBit(P16_44_DPTX_MEAS_ERROR_FLG1, _BIT7);

    // HSync Period
    pstMeasureSyncHV->usHSPeriod = ((((WORD)ScalerGetByte(P16_45_DPTX_MEAS_HS_PERIOD_A_M) & 0x1F) << 8) | (ScalerGetByte(P16_46_DPTX_MEAS_HS_PERIOD_A_L))) + 1;

    // VSync Period
    pstMeasureSyncHV->usVSPeriod = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    // HSync Pulse Width
    pstMeasureSyncHV->usHSWidth = ((((WORD)ScalerGetByte(P16_4A_DPTX_MEAS_HS_PULSE_A_M) & 0x1F) << 8) | (ScalerGetByte(P16_4B_DPTX_MEAS_HS_PULSE_A_L))) + 1;

    // VSync Pulse Width
    pstMeasureSyncHV->usVSWidth = ((((WORD)ScalerGetByte(P16_4C_DPTX_MEAS_VS_PULSE_A_M) & 0xF) << 8) | (ScalerGetByte(P16_4D_DPTX_MEAS_VS_PULSE_A_L))) + 1;

    // H total
    pstMeasureSyncHV->usHTotal = ((((WORD)ScalerGetByte(P16_4E_DPTX_MEAS_HS_PERIOD_D_M) & 0x1F) << 8) | (ScalerGetByte(P16_4F_DPTX_MEAS_HS_PERIOD_D_L))) + 1;

    // V Height
    pstMeasureSyncHV->usVHeight = ((((WORD)ScalerGetByte(P16_51_DPTX_MEAS_VS_PERIOD_D_M) & 0x0F) << 8) | (ScalerGetByte(P16_52_DPTX_MEAS_VS_PERIOD_D_L))) + 1;

    // H Width
    pstMeasureSyncHV->usHWidth = ((((WORD)ScalerGetByte(P16_53_DPTX_MEAS_HS_PULSE_D_M) & 0x1F) << 8) | (ScalerGetByte(P16_54_DPTX_MEAS_HS_PULSE_D_L))) + 1;

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure function for DPTX SST D0
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpTxMeasureInputInfo(void)
{
    StructMeasureSyncData stMeasureSyncHV;
    memset(&stMeasureSyncHV, 0, sizeof(StructMeasureSyncData));

    // Power up DPTX measure; Measure Time Clock = 16384 Xtal; VS Measure Invert Disable; Disable HS/DEN swap
    ScalerSetBit(P16_41_DPTX_MEAS_CTL0, ~(_BIT7 | _BIT6 | _BIT4 | _BIT3 | _BIT0), (_BIT7 | _BIT6));

    // Check Hs/Vs edge location
    switch(ScalerGetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, (_BIT7 | _BIT6 | _BIT5)))
    {
        case (_BIT6 | _BIT5):
            // 011: delay Vs
            ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), _BIT3);
            break;
        case (_BIT5):
            // 001: delay Hs
            ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), _BIT4);
            break;
        default:
            // reset Hs/Vs delay
            ScalerSetBit(P16_5A_DPTX_MEAS2_HS_VS_DLY, ~(_BIT4 | _BIT3), 0x00);
            break;
    }

    // Disable DPTX measure
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~(_BIT5 | _BIT0), 0x00);

    // Set DPTX VGIP sync polarity to default
    ScalerSetBit(P16_A1_DPTX_VGIP_SIGINV, ~(_BIT3 | _BIT2), 0x00);

    // Stop auto-function measure
    ScalerSetByte(P16_CD_DPTX_AUTO_ADJ_CTRL1, 0x80);

    // Set DPTX auto H boundary = 0x0000 ~ 0x1FFF
    ScalerSetByte(P16_C0_DPTX_H_BOUNDARY_H, 0x0F);
    ScalerSetByte(P16_C1_DPTX_H_BOUNDARY_STA_L, 0x00);
    ScalerSetByte(P16_C2_DPTX_H_BOUNDARY_END_L, 0xFF);
    ScalerSetBit(P16_C7_DPTX_GRN_NOISE_MARGIN, ~(_BIT1 | _BIT0), _BIT0);

    // Set DPTX auto V boundary = 0x0000 ~ 0x0FFF
    ScalerSetByte(P16_C3_DPTX_V_BOUNDARY_H, 0x0F);
    ScalerSetByte(P16_C4_DPTX_V_BOUNDARY_STA_L, 0x00);
    ScalerSetByte(P16_C5_DPTX_V_BOUNDARY_END_L, 0xFF);

    // Start DPTX measure
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~(_BIT5 | _BIT0), (_BIT5 | _BIT0));

    // Pop-out measure result
    if(ScalerDpTxMeasureGetMeasureResult(&stMeasureSyncHV) == _FALSE)
    {
        DebugMessageMst("Tx Measure Pop Up Failed", 0x00);

        return _FALSE;
    }

#if(_DP_FREESYNC_SUPPORT == _ON)
    if(GET_DP_MST_FREESYNC_ENABLED() == _TRUE)
    {
        // Set DPTX VGIP sync polarity
        ScalerSetBit(P16_A1_DPTX_VGIP_SIGINV, ~(_BIT6 | _BIT3 | _BIT2), (_BIT6 | ((stMeasureSyncHV.b1VSP == _POSITIVE) ? 0x00 : _BIT3) | ((stMeasureSyncHV.b1HSP == _POSITIVE) ? 0x00 : _BIT2)));
    }
    else
#endif
    {
        // Set DPTX VGIP sync polarity
        ScalerSetBit(P16_A1_DPTX_VGIP_SIGINV, ~(_BIT3 | _BIT2), ((stMeasureSyncHV.b1VSP == _POSITIVE) ? 0x00 : _BIT3) | ((stMeasureSyncHV.b1HSP == _POSITIVE) ? 0x00 : _BIT2));
    }

    // Start auto
    ScalerSetBit(P16_CD_DPTX_AUTO_ADJ_CTRL1, ~_BIT0, _BIT0);

    // Wait for auto
    if(ScalerTimerPollingFlagProc(90, P16_CD_DPTX_AUTO_ADJ_CTRL1, _BIT0, 0x00) == _FALSE)
    {
        DebugMessageMst("Tx Measure Auto Failed", 0x00);

        return _FALSE;
    }

    // Update auto-function V result
    g_stDPTxInputTimingInfo.usVStart = (((WORD)(ScalerGetByte(P16_CE_DPTX_VER_START_END_H) & 0xF0) << 4) | ScalerGetByte(P16_CF_DPTX_VER_START_L));
    g_stDPTxInputTimingInfo.usVHeight = ((((WORD)(ScalerGetByte(P16_CE_DPTX_VER_START_END_H) & 0x0F) << 8) | ScalerGetByte(P16_D0_DPTX_VER_END_L))) - g_stDPTxInputTimingInfo.usVStart + 1;

    // Update auto-function H result (13-bit)
    g_stDPTxInputTimingInfo.usHStart = (((WORD)ScalerGetBit(P16_C8_DPTX_BLU_NOISE_MARGIN, _BIT1) << 11) |
                                        ((WORD)ScalerGetBit(P16_D1_DPTX_H_START_END_H, 0xF0) << 4) |
                                        (ScalerGetByte(P16_D2_DPTX_H_START_L))) + 1;
    g_stDPTxInputTimingInfo.usHWidth = (((WORD)ScalerGetBit(P16_C8_DPTX_BLU_NOISE_MARGIN, _BIT0) << 12) |
                                        ((WORD)ScalerGetBit(P16_D1_DPTX_H_START_END_H, 0x0F) << 8) |
                                        (ScalerGetByte(P16_D3_DPTX_H_END_L))) + 1;
    g_stDPTxInputTimingInfo.usHWidth = g_stDPTxInputTimingInfo.usHWidth - g_stDPTxInputTimingInfo.usHStart + 1;

    // Update off-line measure result
    g_stDPTxInputTimingInfo.b1HSP = stMeasureSyncHV.b1HSP;
    g_stDPTxInputTimingInfo.b1VSP = stMeasureSyncHV.b1VSP;
    g_stDPTxInputTimingInfo.usHSWidth = ((DWORD)((stMeasureSyncHV.b1HSP == _TRUE) ? stMeasureSyncHV.usHSWidth : (stMeasureSyncHV.usHSPeriod - stMeasureSyncHV.usHSWidth)) * GET_DP_TX_INPUT_PIXEL_CLK() * 100) / _MEASURE_CLK;
    g_stDPTxInputTimingInfo.usVSWidth = ((stMeasureSyncHV.b1VSP == _TRUE) ? stMeasureSyncHV.usVSWidth : (stMeasureSyncHV.usVSPeriod - stMeasureSyncHV.usVSWidth));
    g_stDPTxInputTimingInfo.usVTotal = stMeasureSyncHV.usVSPeriod;
    g_stDPTxInputTimingInfo.usHTotal = stMeasureSyncHV.usHTotal;
    g_stDPTxInputTimingInfo.usHFreq = (_MEASURE_CLK * 10 * 2 / stMeasureSyncHV.usHSPeriod + 1) / 2;
    g_stDPTxInputTimingInfo.usVFreq = (_MEASURE_CLK * 1000 * 10 * 2 / stMeasureSyncHV.usHSPeriod / stMeasureSyncHV.usVSPeriod + 1) / 2;

    DebugMessageMst("Tx Measure Done!!", 0x00);

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Clone Check Interlace VTotal Odd
// Input Value  : None
// Output Value : _ODD/ _EVEN
//--------------------------------------------------
bit ScalerDpTxCloneCheckInterlaceVtotal(void)
{
    // Enable One Frame Measure
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT0, 0x00);
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT0, _BIT0);

    ScalerTimerPollingFlagProc(90, P16_42_DPTX_MEAS_CTL1, _BIT7, 0x00);

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // VSync Period
    PDATA_WORD(0) = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    // Delay One Frame Plus 2ms Margin
    ScalerTimerDelayXms(10000 / g_stDPTxInputTimingInfo.usVFreq + 2);

    // Pop up measurement result
    ScalerSetBit(P16_42_DPTX_MEAS_CTL1, ~_BIT6, _BIT6);

    // VSync Period
    PDATA_WORD(1) = ((((WORD)ScalerGetByte(P16_48_DPTX_MEAS_VS_PERIOD_A_M) & 0x0F) << 8) | (ScalerGetByte(P16_49_DPTX_MEAS_VS_PERIOD_A_L))) + 1;

    DebugMessageMst("Clone Check Interlace Vtotal 1", PDATA_WORD(0));
    DebugMessageMst("Clone Check Interlace Vtotal 2", PDATA_WORD(1));

    if(PDATA_WORD(0) == PDATA_WORD(1))
    {
        return _EVEN;
    }
    else
    {
        // Set VTotal As the Smaller One
        g_stDPTxInputTimingInfo.usVTotal = (PDATA_WORD(0) < PDATA_WORD(1)) ? PDATA_WORD(0) : PDATA_WORD(1);
    }

    return _ODD;
}

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
void ScalerDpTxCloneOutputProc(BYTE ucInputPort, BYTE ucPortType, bit bClone)
{
    BYTE ucTemp = 0;

    // Do Nothing if Downstram unplug
    if(GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS() == _DP_UNPLUG)
    {
        return;
    }

    // Only do This when Input is not DP or DP MST is Off
    if((ucPortType != _PORT_DP) || (GET_REG_DP_RX_MST_ENABLE() == _DISABLE))
    {
        if(bClone == _FALSE)
        {
            DebugMessageMst("Clone Off", 0);

            if(GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE)
            {
                ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

                if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }
        }
        else
        {
            if((GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_NONE) && (GET_DP_TX_EXCEED_LINK_BANDWIDTH() == _FALSE))
            {
                // Check if Input Port is Supported
                if(ScalerDpTxCloneCheckInputPortSupport(ucInputPort) == _FALSE)
                {
                    return;
                }

                DebugMessageMst("ScalerDpTxCloneOutputProc", GET_DP_TX_STREAM_SOURCE());

                ScalerDpTxAuxNativeRead(0x00, 0x06, 0x00, 1, &ucTemp);

                pData[1] = 0x00;
                ScalerDpTxAuxNativeWrite(0x00, 0x01, 0x11, 1, &pData[1]);

                // Link Training if Required
                if(((GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_TRAINING)) || (ucTemp != 0x01))
                {
                    DebugMessageMst("Clone Mode Tx State Not Link ON", GET_DP_TX_MODE_STATE());

                    SET_DP_TX_FORCE_LINK_TRAINING();
                    return;
                }

                if((ucPortType == _PORT_DP) && (ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE))
                {
                    if(GET_DP_TX_HDCP_AUTH_STATE() == _DP_TX_HDCP_STATE_IDLE)
                    {
                        DebugMessageMst("Dp TX Clone: HDCP Reauthen", ucInputPort);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_REAUTH);

                        return;
                    }
                }

                // Set Format Conversion for DP Tx Input
                switch(ucInputPort)
                {
#if(_A0_INPUT_PORT_TYPE != _A0_NO_PORT)
                    case _A0_INPUT_PORT:

                        // Set source index to A0
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_ADC << 4));

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_A0_INPUT_PIXEL_CLK());

                        break;
#endif

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

                    case _D0_INPUT_PORT:

#if((_D6_INPUT_PORT_TYPE != _D6_NO_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
                    case _D6_INPUT_PORT:
#endif
                        // Set source index to D0
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D0 << 4));

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D0_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D0_PORT);
#endif
                        break;
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
                    case _D1_INPUT_PORT:

                        // Set source index to D1
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D1 << 4));

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D1_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D1_PORT);
#endif
                        break;
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
                    case _D2_INPUT_PORT:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
                        // Modify input port select for dual-DVI cases
                        if(ScalerTMDSRx2GetDualDVIMode() == _FALSE)
                        {
                            // Set source index to D3
                            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D3 << 4));
                        }
                        else
#endif
                        {
                            // Set source index to D2
                            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D2 << 4));
                        }

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D2_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D2_PORT);
#endif
                        break;
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
                    case _D3_INPUT_PORT:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
                        // Set source index to D4
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D4 << 4));
#else
                        // Set source index to D3
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D3 << 4));
#endif

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D3_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D3_PORT);
#endif
                        break;
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
                    case _D4_INPUT_PORT:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
                        // Modify input port select for dual-DVI cases
                        if(ScalerTMDSRx4GetDualDVIMode() == _FALSE)
                        {
                            // Set source index to D5
                            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D5 << 4));
                        }
                        else
#endif
                        {
                            // Set source index to D4
                            ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D4 << 4));
                        }

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D4_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D4_PORT);
#endif
                        break;
#endif

#if(_D5_INPUT_PORT_TYPE != _D5_NO_PORT)
                    case _D5_INPUT_PORT:

                        // Set source index to D5
                        ScalerSetBit(P31_02_FC_INPUT_DPTX_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_FC_SOURCE_D5 << 4));

                        // Set Dp Tx Pixel Clk
                        SET_DP_TX_INPUT_PIXEL_CLK(GET_D5_INPUT_PIXEL_CLK());

#if((_AUDIO_SUPPORT == _ON) && (_LINE_IN_AUDIO_DP_TX_CLONE_SUPPORT == _OFF))
                        // Set Audio Input Port for DP Tx
                        ScalerSetBit(P6F_02_MUX_DP_I2S_IN, ~(_BIT2 | _BIT1 | _BIT0), _AUDIO_FROM_D5_PORT);
#endif
                        break;
#endif

                    default:
                        break;
                }

                // Get Tx Input Timing
                if(ScalerDpTxMeasureInputInfo() == _TRUE)
                {
                    // Set Color Space
                    switch(GET_COLOR_SPACE(ucInputPort))
                    {
                        case _COLOR_SPACE_RGB:
                            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_RGB);
                            break;

                        case _COLOR_SPACE_YCBCR444:
                            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR444);
                            break;

                        case _COLOR_SPACE_YCBCR422:
                            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);
                            break;

                        case _COLOR_SPACE_YCBCR420:
                            SET_DP_TX_INPUT_COLOR_SPACE(_COLOR_SPACE_YCBCR422);

                            // Set Dp Tx Pixel Clk
                            SET_DP_TX_INPUT_PIXEL_CLK(GET_DP_TX_INPUT_PIXEL_CLK() << 1);
                            break;

                        default:
                            break;
                    }

                    DebugMessageMst("Get DP Tx Color Space", GET_DP_TX_INPUT_COLOR_SPACE());

                    // Set Color Depth
                    switch(GET_COLOR_DEPTH(ucInputPort))
                    {
                        case _COLOR_DEPTH_6_BITS:
                            SET_DP_TX_INPUT_COLOR_DEPTH(0x00);
                            break;

                        case _COLOR_DEPTH_8_BITS:
                            SET_DP_TX_INPUT_COLOR_DEPTH(0x01);
                            break;

                        case _COLOR_DEPTH_10_BITS:
                            SET_DP_TX_INPUT_COLOR_DEPTH(0x02);
                            break;

                        case _COLOR_DEPTH_12_BITS:
                            SET_DP_TX_INPUT_COLOR_DEPTH(0x03);
                            break;

                        case _COLOR_DEPTH_16_BITS:
                            SET_DP_TX_INPUT_COLOR_DEPTH(0x04);
                            break;

                        default:
                            break;
                    }

                    DebugMessageMst("Get DP Tx Color Depth", GET_DP_TX_INPUT_COLOR_DEPTH());

                    if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
                    {
                        SET_DP_TX_INPUT_INTERLACE_MODE(_ON);

                        SET_DP_TX_INPUT_INTERLACE_VTOTAL_NUMBER(ScalerDpTxCloneCheckInterlaceVtotal());
                    }
                    else
                    {
                        SET_DP_TX_INPUT_INTERLACE_MODE(_OFF);
                    }

                    if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_Y_ONLY)
                    {
                        pData[4] = GET_COLOR_DEPTH(ucInputPort);
                    }
                    else if(GET_DP_TX_INPUT_COLOR_SPACE() == _COLOR_SPACE_YCBCR422)
                    {
                        pData[4] = GET_COLOR_DEPTH(ucInputPort) * 2;
                    }
                    else
                    {
                        pData[4] = GET_COLOR_DEPTH(ucInputPort) * 3;
                    }

                    // Get Link Bandwidth 0.1MHz
                    PDATA_DWORD(0) = (DWORD) GET_DP_TX_DOWNSTREAM_LANE_NUM() * _DP_TX_LINK_CLK_MHZ * 8 * 10;

                    // Check if Link BW is enough
                    if(PDATA_DWORD(0) >= ((DWORD) GET_DP_TX_INPUT_PIXEL_CLK() * pData[4] * 1006 / 1000))
                    {
                        ScalerDpTxSetStreamSource(_DP_TX_SOURCE_CLONE);
                    }
                    else
                    {
                        DebugMessageMst("Link BW is not enough for DP TX Clone", ((DWORD) GET_DP_TX_INPUT_PIXEL_CLK() * pData[4] * 1006 / 1000));

                        SET_DP_TX_EXCEED_LINK_BANDWIDTH();
                    }

                    DebugMessageMst("DP Tx Measure Done Set Source", GET_DP_TX_STREAM_SOURCE());
                }
            }
            else
            {
                DebugMessageMst("No Clone!! Stream Source", GET_DP_TX_STREAM_SOURCE());

                if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
                {
                    DebugMessageMst("Tx Link Fail=> Reset Stream", GET_DP_TX_STREAM_SOURCE());

                    ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);
                }

                if(ScalerDpTxCloneGetCurrentInputPort() != ucInputPort)
                {
                    DebugMessageMst("DP TX Clone: Changed Input Port", ucInputPort);

                    ScalerDpTxSetStreamSource(_DP_TX_SOURCE_NONE);

                    if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                    }
                }
            }
        }
    }
}

//--------------------------------------------------
// Description  : DP Tx Clone Output Process
// Input Value  : Input Port Type to be Cloned
// Output Value : None
//--------------------------------------------------
BYTE ScalerDpTxCloneGetCurrentInputPort(void)
{
    switch(ScalerGetBit(P31_02_FC_INPUT_DPTX_SEL, _BIT7 | _BIT6 | _BIT5 | _BIT4) >> 4)
    {
        case _FC_SOURCE_ADC:

            return _A0_INPUT_PORT;

        case _FC_SOURCE_D0:

            return _D0_INPUT_PORT;

        case _FC_SOURCE_D1:

            return _D1_INPUT_PORT;

        case _FC_SOURCE_D2:

            return _D2_INPUT_PORT;

        case _FC_SOURCE_D3:

#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
            // Modify input port select for dual-DVI cases
            if(ScalerTMDSRx2GetDualDVIMode() == _FALSE)
            {
                return _D2_INPUT_PORT;
            }
#endif
            return _D3_INPUT_PORT;

        case _FC_SOURCE_D4:

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)
            return _D3_INPUT_PORT;
#else
            return _D4_INPUT_PORT;
#endif

        case _FC_SOURCE_D5:

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            // Modify input port select for dual-DVI cases
            if(ScalerTMDSRx4GetDualDVIMode() == _FALSE)
            {
                return _D4_INPUT_PORT;
            }
#endif

            return _D5_INPUT_PORT;

        default:
            break;
    }

    return _NO_INPUT_PORT;
}

#if(_DP_MST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Generation of Dp Tx Connection Status Notify MSG Check
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit ScalerDpTxGenConnectStatusNotifyMsgCheck(void)
{
    if((GET_REG_DP_DPCD_INFO(0x00, 0x01, 0x11) & _BIT1) == 0x00)
    {
        return _FALSE;
    }

    if(GET_DP_RX_MST_MODE_STATE() == _DP_RX_MST_MODE_STATUS_NONE_MSG)
    {
        return _FALSE;
    }

    if(GET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE() == _FALSE)
    {
        if(GET_DP_RX_REPORT_DOWNSTREAM_DP_CABLE_STATUS() == GET_DP_TX_DOWNSTREAM_DPPLUG_STATUS())
        {
            return _FALSE;
        }
        else
        {
            // Record Tx Status Change to Wait Safe interval time to issue Up Request MSG
            SET_DP_TX_DOWNSTREAM_DPPLUG_CHANGE();
        }
    }

    if(ScalerDpRxMstCheckMsgBufferFree() != _TRUE)
    {
        return _FALSE;
    }

    CLR_DP_TX_DOWNSTREAM_DPPLUG_CHANGE();

    return _TRUE;
}

//--------------------------------------------------
// Description  : Update Downstream Sink Count
// Input Value  : None
// Output Value : Ture or False
//--------------------------------------------------
bit ScalerDpTxSinkCountUpdate(void)
{
    if(g_enumDpMSTCapablePort != _DP_MST_NO_PORT)
    {
        // Read Sink Count
        if(ScalerDpTxAuxNativeRead(0x00, 0x02, 0x00, 1, pData) == _FALSE)
        {
            return _FALSE;
        }

        // Set Rx Sink Count
        pData[1] = GET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00);
        pData[1] = ((pData[1] & _BIT6) | (pData[0] & 0xBF)) + 1;
        SET_REG_DP_DPCD_INFO(0x00, 0x02, 0x00, pData[1]);
    }

    return _TRUE;
}
#endif

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPHandler(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_EVENT();

    if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_TIMEOUT)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_R0_PASS)
    {
        SET_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(ScalerSyncDpHdcpGetUpstreamEvent() == _DP_RX_HDCP_UPSTREAM_AUTH_EVENT_STOP_ENCRYPTION)
    {
        CLR_DP_TX_HDCP_AUTH_START();

        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
    }
    else if(GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL) == _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL)
    {
        CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL);

        if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
        {
            ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

            SET_DP_TX_HDCP_AUTH_START();

            ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }
    else if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_LINK_ON)
    {
        if(GET_DP_TX_HDCP_AUTH_STATE() != _DP_TX_HDCP_STATE_IDLE)
        {
            ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
        }
    }

    if((GET_DP_TX_HDCP_AUTH_STATE() >= _DP_TX_HDCP_STATE_AUTH_2) && (GET_DP_TX_STREAM_SOURCE() != _DP_TX_SOURCE_NONE))
    {
        if(ScalerSyncDpHdcpGetUpstreamEncryptStatus() == _TRUE)
        {
            if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _FALSE)
            {
                ScalerDpTxHDCPEncryptSignalProc(_ENABLE);
            }
        }
        else
        {
            if(GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE)
            {
                ScalerDpTxHDCPEncryptSignalProc(_DISABLE);
            }
        }
    }

    switch(GET_DP_TX_HDCP_AUTH_STATE())
    {
        case _DP_TX_HDCP_STATE_IDLE:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
                CLR_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                CLR_DP_TX_HDCP_AUTH_HOLD();

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                ScalerDpTxHDCPEncryptSignalProc(_DISABLE);

                ScalerDpTxHDCPCheckDownstreamCapability();

                ScalerDpTxHDCPResetInfo();
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED() == _TRUE)
            {
                if((GET_DP_TX_MODE_STATE() == _DP_TX_MODE_STATUS_LINK_ON) && (GET_DP_TX_HDCP_AUTH_START() == _TRUE))
                {
                    CLR_DP_TX_HDCP_AUTH_START();
                    CLR_DP_TX_IRQ_HDCP_TYPE();

                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                if(ScalerDpTxHDCPAuth1Proc() == _SUCCESS)
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0);
                }
                else
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_1_COMPARE_R0:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                // Wait 100ms to read R0'
                ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_TO_READ_R0);

                SET_DP_TX_HDCP_AUTH_HOLD();
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_HOLD();
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_R0_AVAILABLE);

                if(ScalerDpTxHDCPAuth1CompareR0() == _SUCCESS)
                {
                    if(GET_DP_TX_HDCP_DOWNSTREAM_REPEATER() == _TRUE)
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_2);
                    }
                    else
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                }
                else
                {
                    SET_DP_TX_HDCP_AUTH_START();

                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                }
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_2:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();

                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);
                ScalerTimerActiveTimerEvent(SEC(0.25), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY() == _TRUE)
            {
                CLR_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
                CLR_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();

                if(ScalerDpTxHDCPPollingCpIrqType() == _DP_TX_IRQ_HDCP_V_READY)
                {
                    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT();
                }
                else
                {
                    ScalerTimerActiveTimerEvent(SEC(0.1), _SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                }
            }

            if((GET_DP_TX_IRQ_HDCP_TYPE(_DP_TX_IRQ_HDCP_V_READY) == _DP_TX_IRQ_HDCP_V_READY) ||
               (GET_DP_TX_HDCP_DOWNSTREAM_V_READY_BIT() == _TRUE))
            {
                CLR_DP_TX_IRQ_HDCP_TARGET_TYPE(_DP_TX_IRQ_HDCP_V_READY);

                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_WAITING_FOR_V_READY);

                if(ScalerDpTxHDCPCheckBinfo() == _TRUE)
                {
                    if(ScalerDpTxHDCPAuth2Proc() == _SUCCESS)
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_AUTH_PASS);

                        SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_PASS);
                    }
                    else
                    {
                        ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
                    }
                }
                else
                {
                    ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);

                    SET_DP_TX_HDCP_DOWNSTREAM_EVENT(_DP_TX_HDCP_DOWNSTREAM_AUTH_EVENT_DEVICE_DEPTH_MAX);
                }
            }

            if(GET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT() == _TRUE)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_DP_TX_HDCP_POLLING_V_READY);

                SET_DP_TX_HDCP_AUTH_START();

                ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        case _DP_TX_HDCP_STATE_AUTH_PASS:

            if(GET_DP_TX_HDCP_AUTH_STATE_CHANGE() == _TRUE)
            {
                CLR_DP_TX_HDCP_AUTH_STATE_CHANGE();
            }

            if((ScalerGetByte(PBB_64_HDCP_ECF_BYTE0) != 0x7F) && (GET_DP_TX_STREAM_SOURCE() == _DP_TX_SOURCE_MST) && (GET_DP_TX_HDCP_ENCRYPT_STATUS() == _TRUE))
            {
                // Set ECF by FW
                ScalerSetByte(PBB_64_HDCP_ECF_BYTE0, 0x7F);
                ScalerSetByte(PBB_65_HDCP_ECF_BYTE1, 0xFF);
                ScalerSetByte(PBB_66_HDCP_ECF_BYTE2, 0xFF);
                ScalerSetByte(PBB_67_HDCP_ECF_BYTE3, 0xFF);
                ScalerSetByte(PBB_68_HDCP_ECF_BYTE4, 0xFF);
                ScalerSetByte(PBB_69_HDCP_ECF_BYTE5, 0xFF);
                ScalerSetByte(PBB_6A_HDCP_ECF_BYTE6, 0xFF);
                ScalerSetByte(PBB_6B_HDCP_ECF_BYTE7, 0xFF);

                // Double Buffer by ACT
                SET_REG_DP_RX_SEND_ACT_ENABLE();
            }

            if(GET_DP_TX_HDCP_AUTH_START() == _TRUE)
            {
                ScalerDpTxHDCPChangeAuthState(_DP_TX_HDCP_STATE_IDLE);
            }

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : Check Downstream HDCP Capability
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPCheckDownstreamCapability(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

    if(GET_DP_TX_MODE_STATE() != _DP_TX_MODE_STATUS_UNPLUG)
    {
        // Read HDCP capability from DPCD table of DownStream
        if(ScalerDpTxAuxNativeRead(0x06, 0x80, 0x28, 1, pData) == _TRUE)
        {
            // Check if Rx HDCP is capable
            if((pData[0] & _BIT0) == _BIT0)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
            }

            // Check if Rx is repeater
            if((pData[0] & _BIT1) == _BIT1)
            {
                SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

                ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
            }
        }
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1Proc(void)
{
    // Enable DP Tx HDCP Tx function .
    ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

    // Step1: Read Bcap from DPCD
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x28, 1, pData);

    // Check if Downstream's HDCP is capable
    if((pData[0] & _BIT0) == _BIT0)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_SUPPORTED();

        return _FAIL;
    }

    // Check if Downstream is HDCP repeater
    if((pData[0] & _BIT1) == _BIT1)
    {
        SET_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, _BIT4);
    }
    else
    {
        CLR_DP_TX_HDCP_DOWNSTREAM_REPEATER();

        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT4, 0x00);
    }

    // Step2: Check Bksv
    if(ScalerDpTxHDCPAuth1CheckBksv() == _FAIL)
    {
        SET_DP_TX_HDCP_AUTH_START();

        return _FAIL;
    }

    // Step3: Generate An
    ScalerDpTxHDCPAuth1GenAn();

    // Step4: Write Akey and write Aksv
    ScalerDpTxHDCPAuth1WriteAnAkey();

    // Step5: Geneate Km,Ks,M0 and R0
    if(ScalerDpTxHDCPAuth1GenKm() == _FAIL)
    {
        return _FAIL;
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Check Bksv
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1CheckBksv(void)
{
    bit bResult = _FAIL;

    // Read Bksv
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x00, 5, pData);

    ScalerWrite(PBB_4F_BKSV_0, 5, pData, _AUTOINC);

    // Turn on circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, _BIT2);

    if(ScalerTimerPollingFlagProc(5, PBB_56_DP_HDCP_TX, _BIT1, 1) == _SUCCESS)
    {
        bResult = (ScalerGetBit(PBB_56_DP_HDCP_TX, _BIT0) == 0x00) ? _SUCCESS : _FAIL;
    }
    else
    {
        bResult = _FAIL;
    }

    // Turn Off circuit that check BKSV
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT2, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen An
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth1GenAn(void)
{
    // Write an_gen_start = 1 , and An gen start to run
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, _BIT3);

    // Write reg_freerun_init an initial value
    ScalerSetByte(PBB_58_DP_HDCP_AN_SEED, TL2);

    // Write reg_freerun_init_en 0 to 1 to load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Write an_gen_start = 0 , An gen stop
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, 0x00);

    // Disable load init value
    ScalerSetBit(PBB_56_DP_HDCP_TX, ~_BIT3, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1- Gen Aksv
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth1WriteAnAkey(void)
{
    BYTE ucI = 0;

    for(ucI = 0; ucI < 8; ucI++)
    {
        pData[ucI] = ScalerGetByte(PBB_3B_AN_BYTE_0 - ucI);
    }

    // Write An to Downstream DPCD
    ScalerDpTxAuxNativeWrite(0x06, 0x80, 0x0C, 8, pData);

    // Write Aksv to Downstream DPCD
    ScalerDpTxAuxNativeWrite(0x06, 0x80, 0x07, 5, g_pucHdcpAksvBackup);
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 -Gen Km
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1GenKm(void)
{
    bit bResult = _FAIL;

    // Turn on computation
    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, _BIT1);

    // Km = Akey over Bksv
    // (Ks,M0,R0) = Km,Repeater||An

    if(ScalerTimerPollingFlagProc(5, PBB_31_DPTX_HDCP_CTRL2, _BIT0, 1) == _SUCCESS)
    {
        bResult = _SUCCESS;
    }

    ScalerSetBit(PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, 0x00);

    return bResult;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 1 Compare R0 and R0'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth1CompareR0(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Read R0'
        ScalerDpTxAuxNativeRead(0x06, 0x80, 0x05, 2, pData);

        // Compare R0 and R0'
        if((ScalerGetByte(PBB_4C_R0_BYTE_LSB) == pData[0]) &&
           (ScalerGetByte(PBB_4B_R0_BYTE_MSB) == pData[1]))
        {
            return _SUCCESS;
        }

        ScalerTimerDelayXms(2);

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth2Proc(void)
{
    BYTE ucCompareCounter = 0;

    do
    {
        // Load SHA-1 Input Data
        ScalerDpTxHDCPAuth2WriteShaInput();

        // Compare V and V'
        if(ScalerDpTxHDCPAuth2CompareV() == _SUCCESS)
        {
            return _SUCCESS;
        }

        ucCompareCounter++;
    }
    while(ucCompareCounter < 3);

    SET_DP_TX_HDCP_AUTH_START();

    return _FAIL;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2-Wrtie Data to SHA input
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth2WriteShaInput(void)
{
    WORD usKsvFifoLength = GET_DP_TX_HDCP_DOWNSTREAM_DEVICE_COUNT() * 5;
    WORD usShaInputBitNumbers = 0;
    WORD usKsvLengthTemp = 0;

    // Read KSV FIFO List from Downstream Device
    do
    {
        ScalerDpTxAuxNativeRead(0x06, 0x80, 0x2C, ((usKsvFifoLength > 15) ? 15 : usKsvFifoLength), pData);

        usKsvLengthTemp = 0;

        do
        {
            g_pucDpTxHdcpKsvFifo[usShaInputBitNumbers] = pData[usKsvLengthTemp];

            usKsvLengthTemp++;
            usShaInputBitNumbers++;
        }
        while((usKsvLengthTemp < 15) && (usShaInputBitNumbers < usKsvFifoLength));
    }
    while(usShaInputBitNumbers < usKsvFifoLength);

    // Total bit numbers of SHA-1 input = the length of KSV FIFO + the length of B_info + the length of M0'
    usShaInputBitNumbers = (usKsvFifoLength + 2 + 8) * 8;

    // Reset SHA Block counter
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, _BIT1);

    // Start to Write SHA-1 Transform Input
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT1, 0x00);

    // Initialize The Index of KSV FIFO List
    usKsvLengthTemp = 0;

    // Write the KSV List into SHA-1 Transform Input
    do
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 3]);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }
    while((usKsvFifoLength - usKsvLengthTemp) >= 4);

    // Write the remaining KSV, B info and M0' into SHA-1 Transform Input
    switch(usKsvFifoLength - usKsvLengthTemp)
    {
        case 1:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_43_M0_BYTE_0));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_42_M0_BYTE_1));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_41_M0_BYTE_2));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_40_M0_BYTE_3));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_3F_M0_BYTE_4));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_3E_M0_BYTE_5));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_3D_M0_BYTE_6));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_3C_M0_BYTE_7));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x80);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 2:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_43_M0_BYTE_0));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_42_M0_BYTE_1));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_41_M0_BYTE_2));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_40_M0_BYTE_3));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_3F_M0_BYTE_4));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_3E_M0_BYTE_5));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_3D_M0_BYTE_6));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_3C_M0_BYTE_7));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x80);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        case 3:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp]);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 1]);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, g_pucDpTxHdcpKsvFifo[usKsvLengthTemp + 2]);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_43_M0_BYTE_0));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_42_M0_BYTE_1));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_41_M0_BYTE_2));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_40_M0_BYTE_3));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_3F_M0_BYTE_4));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_3E_M0_BYTE_5));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_3D_M0_BYTE_6));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_3C_M0_BYTE_7));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x80);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;

        default:

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE());
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, GET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH());
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_43_M0_BYTE_0));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_42_M0_BYTE_1));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_41_M0_BYTE_2));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_40_M0_BYTE_3));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, ScalerGetByte(PBB_3F_M0_BYTE_4));
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, ScalerGetByte(PBB_3E_M0_BYTE_5));

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, ScalerGetByte(PBB_3D_M0_BYTE_6));
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, ScalerGetByte(PBB_3C_M0_BYTE_7));
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x80);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;

            if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
            {
                ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
            }

            break;
    }

    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 60)
    {
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 4;

        if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) == 0)
        {
            ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
        }
    }

    // Write 0x00 into the remaining SHA-1 Transform Input space
    if((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) <= 56)
    {
        while((usKsvLengthTemp % _DP_HDCP_SHA1_INPUT_SIZE) < 56)
        {
            ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
            ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
            ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
            ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

            // Enable write 32-bit data to SHA-1 block
            ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

            usKsvLengthTemp += 4;
        }

        // The input length is equal to 2^64
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, 0x00);
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, 0x00);

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        // Write the valid bit numbers into SHA-1 Transform Input
        ScalerSetByte(PBB_5C_DP_HDCP_TX_SHA_DATA_3, 0x00);
        ScalerSetByte(PBB_5D_DP_HDCP_TX_SHA_DATA_2, 0x00);
        ScalerSetByte(PBB_5E_DP_HDCP_TX_SHA_DATA_1, HIBYTE(usShaInputBitNumbers));
        ScalerSetByte(PBB_5F_DP_HDCP_TX_SHA_DATA_0, LOBYTE(usShaInputBitNumbers));

        // Enable write 32-bit data to SHA-1 block
        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT0, _BIT0);

        usKsvLengthTemp += 8;

        ScalerDpTxHDCPAuth2ShaRun((usKsvLengthTemp == _DP_HDCP_SHA1_INPUT_SIZE) ? _TRUE : _FALSE);
    }
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -SHA circuit Run
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPAuth2ShaRun(bit bIsFirst)
{
    // Set First Run For SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT3, ((bIsFirst == _TRUE) ? _BIT3 : 0x00));

    // Run SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~_BIT2, _BIT2);

    ScalerTimerPollingFlagProc(5, PBB_5B_DP_HDCP_TX_SHA_CTRL, _BIT4, _TRUE);

    // Disable First Run and Disable SHA-1 Circuit
    ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT3 | _BIT2), 0x00);
}

//--------------------------------------------------
// Description  : Check Binfo of Downstream port
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPCheckBinfo(void)
{
    // Read Binfo(Device Count and Depth)
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x2A, 2, pData);

    // Check if MAX_DEVS_EXCEEDED or MAX_CASCADE_EXCEEDED is 1 and then abort authentication
    if(((pData[0] & _BIT7) == _BIT7) || ((pData[1] & _BIT3) == _BIT3))
    {
        return _FAIL;
    }

    // Record Binfo of Downstream
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE(pData[0]);
    SET_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH(pData[1]);

    return _TRUE;
}

//--------------------------------------------------
// Description  : Dp Tx HDCP Auth Part 2 -Compare V and V'
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpTxHDCPAuth2CompareV(void)
{
    BYTE ucSha1VHx = 0;
    BYTE ucIndex = 4;

    for(ucSha1VHx = 0; ucSha1VHx < 5; ucSha1VHx++)
    {
        ScalerDpTxAuxNativeRead(0x06, 0x80, (0x14 + (ucSha1VHx * 4)), 4, pData);

        ScalerSetBit(PBB_5B_DP_HDCP_TX_SHA_CTRL, ~(_BIT7 | _BIT6 | _BIT5), ((ucIndex - ucSha1VHx) << 5));

        // Compare V with V'
        if((ScalerGetByte(PBB_63_DP_HDCP_TX_SHA_OUT_0) != pData[0]) ||
           (ScalerGetByte(PBB_62_DP_HDCP_TX_SHA_OUT_1) != pData[1]) ||
           (ScalerGetByte(PBB_61_DP_HDCP_TX_SHA_OUT_2) != pData[2]) ||
           (ScalerGetByte(PBB_60_DP_HDCP_TX_SHA_OUT_3) != pData[3]))
        {
            return _FAIL;
        }

        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4)] = pData[0];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 1] = pData[1];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 2] = pData[2];
        g_pucDpTxHdcpDownStreamV[(ucSha1VHx * 4) + 3] = pData[3];
    }

    return _SUCCESS;
}

//--------------------------------------------------
// Description  : Change HDCP Auth State
// Input Value  : Target HDCP Auth State
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPChangeAuthState(EnumDPTxHDCPAuthState enumHDCPAuthState)
{
    SET_DP_TX_HDCP_AUTH_STATE(enumHDCPAuthState);
    SET_DP_TX_HDCP_AUTH_STATE_CHANGE();
}

//--------------------------------------------------
// Description  : Change HDCP Auth State to Compare R0
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPTimeoutToReadR0Event(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_R0_TIMEOUT();
}

//--------------------------------------------------
// Description  : Waiting for V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPTimeoutForVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_V_READY_TIMEOUT();
}

//--------------------------------------------------
// Description  : Polling V ready of downstream
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPPollingVReadyEvent(void)
{
    SET_DP_TX_HDCP_DOWNSTREAM_POLLING_V_READY();
}

//--------------------------------------------------
// Description  : Polling IRQ status of Downstream
// Input Value  :
// Output Value :
//--------------------------------------------------
EnumDPTxTRQEventHDCPType ScalerDpTxHDCPPollingCpIrqType(void)
{
    ScalerDpTxAuxNativeRead(0x06, 0x80, 0x29, 1, pData);

    if((pData[0] & _BIT3) == _BIT3)
    {
        return _DP_TX_IRQ_HDCP_REAUTH_REQUEST;
    }
    else if((pData[0] & _BIT2) == _BIT2)
    {
        return _DP_TX_IRQ_HDCP_LINK_INTEGRITY_FAIL;
    }
    else if((pData[0] & _BIT1) == _BIT1)
    {
        return _DP_TX_IRQ_HDCP_R0_AVAILABLE;
    }
    else if((pData[0] & _BIT0) == _BIT0)
    {
        return _DP_TX_IRQ_HDCP_V_READY;
    }

    return _DP_TX_IRQ_HDCP_NONE;
}

//--------------------------------------------------
// Description  : Enable HDCP TX Encryption
// Input Value  : _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerDpTxHDCPEncryptSignalProc(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // HDCP encryption enable.
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
    }
    else
    {
        // Disable HDCP function, Encryption and Reset Repeater Flag
        ScalerSetBit(PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);

        // Output MST type
        if(ScalerGetBit(PBB_00_DP_PHY_CTRL, _BIT1) == _BIT1)
        {
            // Set ECF by FW
            ScalerSetByte(PBB_64_HDCP_ECF_BYTE0, 0x00);
            ScalerSetByte(PBB_65_HDCP_ECF_BYTE1, 0x00);
            ScalerSetByte(PBB_66_HDCP_ECF_BYTE2, 0x00);
            ScalerSetByte(PBB_67_HDCP_ECF_BYTE3, 0x00);
            ScalerSetByte(PBB_68_HDCP_ECF_BYTE4, 0x00);
            ScalerSetByte(PBB_69_HDCP_ECF_BYTE5, 0x00);
            ScalerSetByte(PBB_6A_HDCP_ECF_BYTE6, 0x00);
            ScalerSetByte(PBB_6B_HDCP_ECF_BYTE7, 0x00);

            // Double Buffer by ACT
            SET_REG_DP_RX_SEND_ACT_ENABLE();
        }
    }
}

//--------------------------------------------------
// Description  : Reset HDCP TX Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpTxHDCPResetInfo(void)
{
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEVICE();
    CLR_DP_TX_HDCP_DOWNSTREAM_BINFO_DEPTH();

    memset(g_pucDpTxHdcpKsvFifo, 0, sizeof(g_pucDpTxHdcpKsvFifo));
}
#endif // End for #if(_DP_SUPPORT == _ON)

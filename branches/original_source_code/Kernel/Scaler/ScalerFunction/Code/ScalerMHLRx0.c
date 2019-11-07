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
// ID Code      : ScalerMHLRx0.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MHLRX0__

#include "ScalerFunctionInclude.h"

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)

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
BYTE g_ucMHLRx0MhlVersion;
BYTE g_ucMHLRx0AdopterIDH = 0xFF;
BYTE g_ucMHLRx0AdopterIDL = 0xFF;
bit g_bMHLRx0AdopterIDDone = _FALSE;
bit g_bMHLRx0CbusResetForHTCDone = _FALSE;
bit g_bMHLRx0SentMscDcapRdy = _TRUE;
StructMHLProcessInfo g_stMHLRx0Process;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerMHLRx0DetectClkMode(void);
BYTE ScalerMHLRx0DetectClkMode_EXINT0(void);
bit ScalerMHLRx0MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLRx0MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLRx0MscRCPGetCommand(BYTE *pucKeyCode);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx0DetectClkMode(void)
{
    WORD usTemp = 200;

    // Clear Error Flag and Start Detection
    ScalerSetBit(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P26_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit(P26_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        Delay5us(g_ucDelay5usN);
    }

    if(((bit)ScalerGetBit(P26_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit(P26_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX0_CLK_MODE()))
    {
        ScalerSetBit(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 300;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit(P2_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
                  (--usTemp != 0))
            {
                Delay5us(g_ucDelay5usN);
            }

            if(usTemp == 0)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode (EXINT0 Only)
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
BYTE ScalerMHLRx0DetectClkMode_EXINT0(void) using 1
{
    WORD usTemp = 200;

    // Clear Error Flag and Start Detection
    ScalerSetBit_EXINT(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P26_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit_EXINT(P26_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    if(((bit)ScalerGetBit_EXINT(P26_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit_EXINT(P26_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX0_CLK_MODE()))
    {
        ScalerSetBit_EXINT(P26_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX0_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 300;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit_EXINT(P2_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
                  (--usTemp != 0))
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            if(usTemp == 0)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }
        else
        {
            return _FALSE;
        }
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Send MSC HPD Operation for D0 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLRx0MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    BYTE ucResultPacket = 0;

    if(GET_MHL_RX0_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx0MscFIFOSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue, 0, _NULL_POINTER);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_RX0_READY_TO_TRANSMIT();

                return _SUCCESS;
                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX0_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx0MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Send Write Burst Operation for D0 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx0MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    BYTE ucResultPacket = 0;

    if(enumMode == _MHL_WRITE_BURST_WITH_REQ)
    {
        // Clear Grant To Write Flag
        ScalerSetDataPortByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

        // Send Request to Write
        ScalerMHLRx0MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

        // Disable Access Port Auto Increase
        ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

        // Polling Grant to Write
        ScalerSetByte(P28_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
        ScalerTimerPollingFlagProc(100, P28_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

        // Enable Access Port Auto Increase
        ScalerSetBit(P28_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);
    }
    if(GET_MHL_RX0_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx0MscFIFOSendCommand(_MSC_WRITE_BURST, ucOffset, 0x00, ucDataLength, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                // Send Device Scratchpad Change
                ScalerMHLRx0MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_DSCR_CHG);

                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX0_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX0_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx0MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

                return _FAIL;
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _FAIL;
                break;
        }
    }
    else
    {
        return _FAIL;
    }

    return _FAIL;
}

//--------------------------------------------------
// Description  : Get RCP Key Code for D0 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx0MscRCPGetCommand(BYTE *pucKeyCode)
{
    // Check RCP Command
    if((bit)ScalerGetBit(P28_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
    {
        // Clear Flag
        ScalerSetByte(P28_D4_CBUS_CTRL_34, (BYTE)_BIT6);

        pucKeyCode[0] = ScalerGetByte(P28_D9_CBUS_CTRL_39);

        return _TRUE;
    }

    return _FALSE;
}

#endif // End of #if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)


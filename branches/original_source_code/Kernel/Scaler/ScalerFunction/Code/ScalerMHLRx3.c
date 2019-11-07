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
// ID Code      : ScalerMHLRx3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_MHLRX3__

#include "ScalerFunctionInclude.h"

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

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
BYTE g_ucMHLRx3MhlVersion;
BYTE g_ucMHLRx3AdopterIDH = 0xFF;
BYTE g_ucMHLRx3AdopterIDL = 0xFF;
bit g_bMHLRx3AdopterIDDone = _FALSE;
bit g_bMHLRx3CbusResetForHTCDone = _FALSE;
bit g_bMHLRx3SentMscDcapRdy = _TRUE;
StructMHLProcessInfo g_stMHLRx3Process;


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
bit ScalerMHLRx3DetectClkMode(void);
BYTE ScalerMHLRx3DetectClkMode_EXINT0(void);
bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue);
bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode);
bit ScalerMHLRx3MscRCPGetCommand(BYTE *pucKeyCode);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : MHL Detect Clk Mode if 24Bit or PP Mode
// Input Value  : None
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx3DetectClkMode(void)
{
    WORD usTemp = 200;

    // Clear Error Flag and Start Detection
    ScalerSetBit(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P77_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit(P77_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        Delay5us(g_ucDelay5usN);
    }

    if(((bit)ScalerGetBit(P77_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit(P77_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX3_CLK_MODE()))
    {
        ScalerSetBit(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 300;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit(P72_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
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
BYTE ScalerMHLRx3DetectClkMode_EXINT0(void) using 1
{
    WORD usTemp = 200;

    // Clear Error Flag and Start Detection
    ScalerSetBit_EXINT(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P77_A7_MHL_CTRL_07, ~_BIT0, _BIT0);

    // Wait until detection is done(1ms) or timeout(1.5ms)
    while((ScalerGetBit_EXINT(P77_A7_MHL_CTRL_07, _BIT0) == _BIT0) && (--usTemp != 0))
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    if(((bit)ScalerGetBit_EXINT(P77_B3_MHL_CTRL_13, _BIT0) == _TRUE) ||
       ((bit)ScalerGetBit_EXINT(P77_A7_MHL_CTRL_07, _BIT7) != GET_TMDS_RX3_CLK_MODE()))
    {
        ScalerSetBit_EXINT(P77_B3_MHL_CTRL_13, ~(_BIT1 | _BIT0), _BIT0);

        if(GET_TMDS_RX3_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
        {
            usTemp = 300;

            // Wait until RGB detection is done or timeout(3ms)
            while((ScalerGetBit_EXINT(P72_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) != (_BIT7 | _BIT6 | _BIT5)) &&
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
// Description  : Send MSC HPD Operation for D3 Port
// Input Value  : enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
bit ScalerMHLRx3MscSendCommand(EnumMHLMscCommand enumMSCCommand, EnumMHLMscOffset enumMSCOffset, EnumMHLMscData enumMSCValue)
{
    BYTE ucResultPacket = 0;

    if(GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx3MscFIFOSendCommand(enumMSCCommand, enumMSCOffset, enumMSCValue, 0, _NULL_POINTER);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                SET_MHL_RX3_READY_TO_TRANSMIT();

                return _SUCCESS;
                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX3_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx3MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

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
// Description  : Send Write Burst Operation for D3 Port
// Input Value  : ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------
bit ScalerMHLRx3MscSendWriteBurst(BYTE ucOffset, BYTE ucDataLength, BYTE *pucData, EnumMHLWriteBurstMode enumMode)
{
    BYTE ucResultPacket = 0;

    if(enumMode == _MHL_WRITE_BURST_WITH_REQ)
    {
        // Clear Grant To Write Flag
        ScalerSetDataPortByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT, _MSC_GRT_WRT);

        // Send Request to Write
        ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_REQ_WRT);

        // Disable Access Port Auto Increase
        ScalerSetBit(P68_AB_CBUS_CTRL_0B, ~_BIT0, 0x00);

        // Polling Grant to Write
        ScalerSetByte(P68_AC_CBUS_CTRL_0C, _MSC_RCHANGE_INT);
        ScalerTimerPollingFlagProc(100, P68_AD_CBUS_CTRL_0D, _MSC_GRT_WRT, _TRUE);

        // Enable Access Port Auto Increase
        ScalerSetBit(P68_AB_CBUS_CTRL_0B, ~_BIT0, _BIT0);
    }
    if(GET_MHL_RX3_READY_TO_TRANSMIT() == _TRUE)
    {
        ucResultPacket = ScalerMHLRx3MscFIFOSendCommand(_MSC_WRITE_BURST, ucOffset, 0x00, ucDataLength, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                // Send Device Scratchpad Change
                ScalerMHLRx3MscSendCommand(_MSC_SET_INT, _MSC_RCHANGE_INT, _MSC_DSCR_CHG);

                return _SUCCESS;

                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

                CLR_MHL_RX3_READY_TO_TRANSMIT();
                ScalerTimerActiveTimerEvent(SEC(2.5), _SCALER_TIMER_EVENT_MHL_RX3_READY_TO_TRANSMIT);

                return _FAIL;
                break;

            case _MHL_PROTOCOL_ERROR: // Source Reply Data Packet Instead of Control Packet

                ScalerMHLRx3MscFIFOSendCommand(_MSC_ABORT, _MSC_NULL_ADDRESS, _MSC_NULL_VALUE, 0, _NULL_POINTER);

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
// Description  : Get RCP Key Code for D3 Port
// Input Value  : RCP Key Code
// Output Value : True or False
//--------------------------------------------------
bit ScalerMHLRx3MscRCPGetCommand(BYTE *pucKeyCode)
{
    // Check RCP Command
    if((bit)ScalerGetBit(P68_D4_CBUS_CTRL_34, _BIT6) == _TRUE)
    {
        // Clear Flag
        ScalerSetByte(P68_D4_CBUS_CTRL_34, (BYTE)_BIT6);

        pucKeyCode[0] = ScalerGetByte(P68_D9_CBUS_CTRL_39);

        return _TRUE;
    }

    return _FALSE;
}

#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)


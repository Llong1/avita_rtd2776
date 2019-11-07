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
// ID Code      : ScalerDPTxAux.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DPTX_AUX__

#include "ScalerFunctionInclude.h"

#if(_DP_TX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _NATIVE_AUX_WRITE                           0x80
#define _NATIVE_AUX_READ                            0x90
#define _I2C_AUX_WRITE                              0x40
#define _I2C_AUX_READ                               0x50


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//--------------------------------------------------
bit ScalerDpTxAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDpTxAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
bit ScalerDpTxAuxNativeWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray);
bit ScalerDpTxAuxNativeRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);
bit ScalerDpTxAuxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
bit ScalerDpTxAuxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT);
BYTE ScalerDpTxAuxNativeRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray);


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Tx Aux Write
// Input Value  : ucCommand --> Aux Write Command
//                ucHighAddress --> High Byte of  Aux Write Address
//                ucMidAddress --> Middle Byte of  Aux Write Address
//                ucLowAddress --> Low Byte of  Aux Write Address
//                ucLength --> Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of Aux Write
// Output Value : TRUE --> Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxWrite(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    BYTE ucDataCount = 0;
    BYTE ucWriteRetryNum = 0;

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

    // Reset FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Enable AUX FW Handle Mode
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    // Check Length
    if(ucLength == 0)
    {
        // I2C Over Aux Transaction
        if((ucCommandAddrH & _BIT7) == 0x00)
        {
            // Enable I2C Addr Only Mode
            ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT7, _BIT7);
        }
        else
        {
            ucLength = 1;
        }
    }
    else if(ucLength > 16)
    {
        ucLength = 16;
    }

    ScalerSetByte(PBD_A4_AUXTX_REQ_CMD, ucCommandAddrH);
    ScalerSetByte(PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
    ScalerSetByte(PBD_A6_AUXTX_REQ_ADDR_L, ucAddrL);

    // Setting AUX Write Length : TX_LEN = ucLength-1
    ScalerSetByte(PBD_A7_AUXTX_REQ_LEN, ((ucLength > 0) ? (ucLength - 1) : 0));

    // Write Data to Buffer
    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
    {
        ScalerSetByte(PBD_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
    }

    // Reset AUX Start Bit
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

    // Enable Aux to Start Write
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

    while(ucWriteRetryNum < 7)
    {
        // Delay 400us
        for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);
        }

        // Polling AUX Done Bit (Delay 25 Loop = 175us)
        for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
        {
            Delay5us(g_ucDelay5usN);

            if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
            {
                // Reply Error or Nack or Command is not ACK
                if((ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(PBD_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                {
                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Write Data to Buffer
                    for(ucDataCount = 0; ucDataCount < ucLength; ucDataCount++)
                    {
                        ScalerSetByte(PBD_A8_AUXTX_REQ_DATA, pucWriteArray[ucDataCount]);
                    }

                    // Reset AUX Start Bit
                    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                    // Enable Aux to Start Write
                    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

                    break;
                }
                else
                {
                    // Disable Timeout Retry
                    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Enable Short HPD Int.
                    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                    return _TRUE;
                }
            }
            else
            {
                // HW Retry Times Reaches RETRY_NUM
                if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                {
                    // Disable Timeout Retry
                    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                    // CLR Flag
                    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                    // Reset FIFO
                    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                    // Enable Short HPD Int.
                    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                    return _FALSE;
                }
            }
        }

        // Increasing Retry Num
        ucWriteRetryNum += 1;
    }

    // Disable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Aux Read
// Input Value  : ucCommand --> Aux Read Command
//                ucHighAddress --> High Byte of  Aux Read Address
//                ucMidAddress --> Middle Byte of  Aux Read Address
//                ucLowAddress --> Low Byte of  Aux Read Address
//                ucLength --> Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of Aux Read
// Output Value : TRUE --> Aux Read Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxRead(BYTE ucCommandAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucCheckLength = 0;
    BYTE ucOffsetLength = 0;
    BYTE ucRetryAuxReadNum = 0;

    // Disable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable AUX FW Handle Mode & Disable Address only transaction
    ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Setting DPCD Read Address
        ScalerSetByte(PBD_A4_AUXTX_REQ_CMD, ucCommandAddrH);
        ScalerSetByte(PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
        ScalerSetByte(PBD_A6_AUXTX_REQ_ADDR_L, (ucAddrL + ucOffsetLength));

        ucLength = ucLength - ucOffsetLength;

        if(ucLength == 0)
        {
            // I2C Over Aux Transaction
            if((ucCommandAddrH & _BIT7) == 0x00)
            {
                // Enable I2C Addr Only Mode
                ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT7, _BIT7);
            }
            else
            {
                ucLength = 1;
            }
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Set Read Length : TX_LEN = ucLength-1
        ScalerSetByte(PBD_A7_AUXTX_REQ_LEN, ((ucLength > 0) ? (ucLength - 1) : 0));

        // Reset AUX Start Bit
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay 400us
            for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);
            }

            // Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
            {
                Delay5us(g_ucDelay5usN);

                if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit(PBD_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Reset AUX Start Bit
                        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Read
                        ScalerSetBit(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ucCheckLength = ScalerGetBit(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        ucOffsetLength += ucCheckLength;

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = ScalerGetByte(PBD_AA_AUX_REPLY_DATA);
                            pucReadArray++;
                        }

                        if(ucCheckLength >= ucLength)
                        {
                            // Disable Timeout Retry
                            ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            return _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(ScalerGetBit(PBD_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Enable Short HPD Int.
                        ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum += 1;
        }
        while((ucReadRetryNum < 7) && (ScalerGetBit(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00));

        ucRetryAuxReadNum = ucRetryAuxReadNum + 1;
    }
    while((ucCheckLength < ucLength) && (ucRetryAuxReadNum < 7));

    // Disable Timeout Retry
    ScalerSetBit(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    ScalerSetBit(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Write
// Input Value  : ucCommand --> Native Aux Write Command
//                ucHighAddress --> High Byte of  Native Aux Write Address
//                ucMidAddress --> Middle Byte of  Native Aux Write Address
//                ucLowAddress --> Low Byte of  Native Aux Write Address
//                ucLength --> Native Aux Write Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxNativeWrite(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucWriteArray)
{
    if(ScalerDpTxAuxWrite((0x80 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucWriteArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Read
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxNativeRead(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray)
{
    if(ScalerDpTxAuxRead((0x90 | ucAddrH), ucAddrM, ucAddrL, ucLength, pucReadArray) == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Write
//                ucSubAddress --> SubAddress of I2CoverAux Write
//                ucLength --> Length of I2CoverAux Write
//                pWriteArray --> Data of I2CoverAux Write
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxI2CoverWrite(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDpTxAuxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDpTxAuxWrite((0x00 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }
    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx I2CoverAux Write
// Input Value  : ucSlaveAddress --> SlaveAddress of I2CoverAux Read
//                ucSubAddress --> SubAddress of I2CoverAux Read
//                ucLength --> Length of I2CoverAux Read
//                pWriteArray --> Data of I2CoverAux Read
// Output Value : TRUE --> Native Aux Write Sucessful
//--------------------------------------------------
bit ScalerDpTxAuxI2CoverRead(BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray, bit bMOT)
{
    if(ScalerDpTxAuxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
    {
        if(ScalerDpTxAuxRead((0x10 | ((BYTE)bMOT << 6)), 0x00, ucSlaveAddress, ucLength, pucDataArray) == _FALSE)
        {
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Tx Native Aux Read For Int0
// Input Value  : ucCommand --> Native Aux Read Command
//                ucHighAddress --> High Byte of  Native Aux Read Address
//                ucMidAddress --> Middle Byte of  Native Aux Read Address
//                ucLowAddress --> Low Byte of  Native Aux Read Address
//                ucLength --> Native Aux Read Length
//                ucAutoInc --> Address Auto Increase flag
//                pWriteArray --> Data Array of of  Native Aux Read
// Output Value : TRUE --> Native Aux Read Sucessful
//--------------------------------------------------
BYTE ScalerDpTxAuxNativeRead_EXINT0(BYTE ucAddrH, BYTE ucAddrM, BYTE ucAddrL, BYTE ucLength, BYTE *pucReadArray) using 1
{
    BYTE ucDataCount = 0;
    BYTE ucReadRetryNum = 0;
    BYTE ucCheckLength = 0;
    BYTE ucOffsetLength = 0;
    BYTE ucRetryAuxReadNum = 0;

    // Disable Short HPD Int.
    ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, 0x00);

    // Enable AUX FW Handle Mode & Disable Address only transaction
    ScalerSetBit_EXINT(PBD_A3_AUXTX_TRAN_CTRL, ~(_BIT7 | _BIT5), _BIT5);

    do
    {
        ucReadRetryNum = 0;

        // Enable Retry Mechanism
        ScalerSetBit_EXINT(PBD_B0_AUX_RETRY_2, ~_BIT7, 0x00);

        // Enable Timeout HW Retry
        ScalerSetBit_EXINT(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT5));

        // CLR Flag
        ScalerSetByte_EXINT(PBD_B1_AUX_IRQ_EVENT, 0x3F);

        // Reset AUX FIFO
        ScalerSetBit_EXINT(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Setting DPCD Read Address
        ScalerSetByte_EXINT(PBD_A4_AUXTX_REQ_CMD, (0x90 | ucAddrH));
        ScalerSetByte_EXINT(PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
        ScalerSetByte_EXINT(PBD_A6_AUXTX_REQ_ADDR_L, (ucAddrL + ucOffsetLength));

        ucLength = ucLength - ucOffsetLength;

        if(ucLength == 0)
        {
            ucLength = 1;
        }
        else if(ucLength > 16)
        {
            ucLength = 16;
        }

        // Set Read Length : TX_LEN = ucLength-1
        ScalerSetByte_EXINT(PBD_A7_AUXTX_REQ_LEN, (ucLength - 1));

        // Reset AUX Start Bit
        ScalerSetBit_EXINT(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

        // Enable Aux to Start Read
        ScalerSetBit_EXINT(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

        do
        {
            // Delay 400us
            for(ucDataCount = 0; ucDataCount < 55; ucDataCount++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            // Polling AUX Done Bit (Delay 25 Loop = 175us)
            for(ucDataCount = 0; ucDataCount < 25; ucDataCount++)
            {
                Delay5us_EXINT(g_ucDelay5usN);

                if(ScalerGetBit_EXINT(PBD_B1_AUX_IRQ_EVENT, _BIT5) == _BIT5)
                {
                    // Reply Error or Nack or Command is not ACK
                    if((ScalerGetBit_EXINT(PBD_B1_AUX_IRQ_EVENT, _BIT2) != 0x00) || (ScalerGetBit_EXINT(PBD_A9_AUX_REPLY_CMD, (_BIT5 | _BIT4)) != 0x00))
                    {
                        // CLR Flag
                        ScalerSetByte_EXINT(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit_EXINT(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Reset AUX Start Bit
                        ScalerSetBit_EXINT(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, 0x00);

                        // Enable Aux to Start Read
                        ScalerSetBit_EXINT(PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
                    }
                    else
                    {
                        ucCheckLength = ScalerGetBit_EXINT(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
                        ucOffsetLength += ucCheckLength;

                        // Read Data From Buffer
                        for(ucDataCount = 0; ucDataCount < ucCheckLength; ucDataCount++)
                        {
                            *pucReadArray = ScalerGetByte_EXINT(PBD_AA_AUX_REPLY_DATA);
                            pucReadArray++;
                        }

                        if(ucCheckLength >= ucLength)
                        {
                            // Disable Timeout Retry
                            ScalerSetBit_EXINT(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                            // CLR Flag
                            ScalerSetByte_EXINT(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                            // Reset AUX FIFO
                            ScalerSetBit_EXINT(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                            // Enable Short HPD Int.
                            ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                            return _TRUE;
                        }
                    }

                    break;
                }
                else
                {
                    // HW Retry Times Reaches RETRY_NUM
                    if(ScalerGetBit_EXINT(PBD_B1_AUX_IRQ_EVENT, _BIT1) == _BIT1)
                    {
                        // Disable Timeout Retry
                        ScalerSetBit_EXINT(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

                        // CLR Flag
                        ScalerSetByte_EXINT(PBD_B1_AUX_IRQ_EVENT, 0x3F);

                        // Reset AUX FIFO
                        ScalerSetBit_EXINT(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

                        // Enable Short HPD Int.
                        ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

                        return _FALSE;
                    }
                }
            }

            // Increasing Retry Num
            ucReadRetryNum += 1;
        }
        while((ucReadRetryNum < 7) && (ScalerGetBit_EXINT(PBD_AE_AUX_FIFO_WR_PTR, (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00));

        ucRetryAuxReadNum = ucRetryAuxReadNum + 1;
    }
    while((ucCheckLength < ucLength) && (ucRetryAuxReadNum < 7));

    // Disable Timeout Retry
    ScalerSetBit_EXINT(PBD_B0_AUX_RETRY_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // CLR Flag
    ScalerSetByte_EXINT(PBD_B1_AUX_IRQ_EVENT, 0x3F);

    // Reset AUX FIFO
    ScalerSetBit_EXINT(PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable Short HPD Int.
    ScalerSetBit_EXINT(PBB_72_HPD_IRQ_EN, ~_BIT6, _BIT6);

    return _FALSE;
}
#endif // End for #if(_DP_TX_SUPPORT == _ON)

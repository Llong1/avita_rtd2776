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
// ID Code      : ScalerIOSC.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IOSC__

#include "ScalerFunctionInclude.h"

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


//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerIOSCClockDiv(BYTE ucClkDiv);
void ScalerIOSCTrimming(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************

//--------------------------------------------------
// Description  : Set internal oscillator Clock Divider.
// Input Value  : ucClkDiv    --> Clock divider.
// Output Value : None
//--------------------------------------------------
void ScalerIOSCClockDiv(BYTE ucClkDiv)
{
    // Set INOSC Divider to ucClkDiv.
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~(_BIT1 | _BIT0), ucClkDiv);
}

//--------------------------------------------------
// Description  : Internal Oscillator Triming.
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIOSCTrimming(void)
{
    SBYTE chTempInx = 0;

    // Disable auto trimming.
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, 0x00);

    // 27Mhz
    ScalerSetBit(P6_A6_EMB_BGRES1, ~_BIT7, _BIT7);

    // Enable IOSC
    ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~_BIT7, _BIT7);

    ScalerTimerDelayXms(2);

    // Trim Resolution select, Fosc=counter * Fxtal / 1000
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT5, 0x00);

    // Wait time for Internal OSC Stable->15*2^10 Tref
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT4, _BIT4);

    // Wait time for trimming->4*2^10 Tref
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Set internal oscillator divider(Divider = 1)
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~(_BIT1 | _BIT0), _IOSC_DIV);

#if(_INTERNAL_OSC_XTAL == _IOSC27000K)
    // Trimming comparason target 0x75D --> 27M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0x5D);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);

#elif(_INTERNAL_OSC_XTAL == _IOSC28000K)
    // Trimming comparason target 0x7A4 --> 28M
    ScalerSetByte(P6_A1_OSC_TRIM_CTRL1, 0xA4);
    ScalerSetBit(P6_A5_EMB_BGRES, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x07);
#endif

    // Switch to hardware trimming result.
    ScalerSetBit(P6_A2_OSC_TRIM_CTRL2, ~_BIT7, 0x00);

    // Thermal compensation factor, 11 for the best
    ScalerSetBit(P6_A6_EMB_BGRES1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Enable trimming
    ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, _BIT7);

    //-------Use manual mode go back recheck best step start --------
    // Wait for auto trimming stop, time-consuming ~= 3.36ms
    if(ScalerTimerPollingFlagProc(10, P6_A0_OSC_TRIM_CTRL0, _BIT6, _TRUE) == _FALSE)
    {
        return;
    }

    // Back up final result of auto trimming
    pData[0] = (ScalerGetBit(P6_A2_OSC_TRIM_CTRL2, (_BIT5 | _BIT4 | _BIT3)) >> 3) | (ScalerGetBit(P6_A2_OSC_TRIM_CTRL2, (_BIT2 | _BIT1 | _BIT0)) << 3);
    pData[3] = ((pData[0] & 0x38) >> 3) | ((pData[0] & 0x07) << 3);

    // Get target iosc cycle counter
    PDATA_WORD(5) = (ScalerGetBit(P6_A5_EMB_BGRES, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) << 8) | ScalerGetByte(P6_A1_OSC_TRIM_CTRL1);

    // Initial variable
    PDATA_WORD(7) = 0xFFF;

    // Change to manual trimming mode
    ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~_BIT6, 0x00);
    ScalerSetBit(P6_A2_OSC_TRIM_CTRL2, ~_BIT7, _BIT7);

    for(chTempInx = -1; chTempInx < 2; chTempInx++)
    {
        pData[1] = pData[0] + chTempInx;
        pData[2] = ((pData[1] & 0x38) >> 3) | ((pData[1] & 0x07) << 3);

        // Apply trimming step
        ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[2] & 0x3F);

        // Restart trimming
        ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, 0x00);
        ScalerSetBit(P6_A0_OSC_TRIM_CTRL0, ~_BIT7, _BIT7);

        // Polling trimming finished, time-cunsuming ~= 440us
        ScalerTimerPollingFlagProc(10, P6_A0_OSC_TRIM_CTRL0, _BIT6, _TRUE);

        // Get iosc cycle counter in current step
        PDATA_WORD(6) = (ScalerGetBit(P6_A5_EMB_BGRES, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) << 4) | ScalerGetByte(P6_A4_OSC_TRIM_CNT);

        // Record minimum step
        if(ABSDWORD(PDATA_WORD(6), PDATA_WORD(5)) < PDATA_WORD(7))
        {
            PDATA_WORD(7) = ABSDWORD(PDATA_WORD(6), PDATA_WORD(5));
            pData[3] = pData[2];
        }
    }

    // Apply the best trimming step
    ScalerSetBit(P6_A3_EMBEDDED_OSC_CTRL, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), pData[3] & 0x3F);
    //-------Use manual mode go back recheck best step end , total time-consuming ~= 5.36ms ----------
}

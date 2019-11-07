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
// ID Code      : ScalerIR.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_IR__

#include "ScalerFunctionInclude.h"

#if(_IR_SUPPORT == _IR_HW_SUPPORT)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _IR_SAMPLE_CLK                  50 // kHz
#define _IR_HW_XTAL_SAMPLE_CLK_DIV      (((WORD)_EXT_XTAL / _IR_SAMPLE_CLK) - 1)
#define _IR_HW_IOSC_SAMPLE_CLK_DIV      (((WORD)_INTERNAL_OSC_XTAL / _IR_SAMPLE_CLK) - 1)

#define _IR_TABLE_1_LENGTH              10
#define _IR_TABLE_2_LENGTH              6
#define _IR_TABLE_3_LENGTH              8
#define _IR_TABLE_4_LENGTH              2

#define _IR_TABLE_1_START               0
#define _IR_TABLE_2_START               (_IR_TABLE_1_LENGTH)
#define _IR_TABLE_3_START               (_IR_TABLE_1_LENGTH + _IR_TABLE_2_LENGTH)
#define _IR_TABLE_4_START               (_IR_TABLE_1_LENGTH + _IR_TABLE_2_LENGTH + _IR_TABLE_3_LENGTH)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
bit g_bIRReceived = 0;
BYTE g_pucIRCode[8];

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerIRHWModeInitial(void);
void ScalerIRHWModeDecoder(BYTE code *pucIRTableArray, BYTE ucBankNum);
bit ScalerIRHWModeGetData(BYTE *pucBuffer);
void ScalerIRHWModeIntHandler_EXINT0(void);
void ScalerIRHWModeClockSel(EnumClkSel enumClock);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : IRDA Initial Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeInitial(void)
{
    // Sample clock divider
    ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
    ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));


    // Clear interrupt flag
    ScalerSetBit(P23_BB_IR_SR3, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Enable HW interrupt
    ScalerSetBit(P23_B2_IR_CR2, ~_BIT2, _BIT2);

    // _BIT0: Enable IR
    ScalerSetBit(P23_B2_IR_CR2, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Set HW IR Table
// Input Value  : User Table
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeDecoder(BYTE code *pucIRTableArray, BYTE ucBankNum)
{
    // P23_A0_IR_PSR0 ~ P23_A9_IR_SF1
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_1_START, _IR_TABLE_1_LENGTH, ucBankNum, P23_A0_IR_PSR0, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_AC_IR_DPIR0 ~ P23_B3_IR_CR3
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_2_START, _IR_TABLE_2_LENGTH, ucBankNum, P23_AE_IR_DPIR2, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_D0_IR_PSR_UP0 ~ P23_D7_IR_PER_UP3
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_3_START, _IR_TABLE_3_LENGTH, ucBankNum, P23_D0_IR_PSR_UP0, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);

    // P23_DA_IR_CTRL_RC62 ~ P23_DB_IR_CTRL_RC63
    ScalerBurstWrite(pucIRTableArray + _IR_TABLE_4_START, _IR_TABLE_3_LENGTH, ucBankNum, P23_DA_IR_CTRL_RC62, _BURSTWRITE_DATA_COMMON_AUTO_INC, _BURSTWRITE_FROM_FLASH);
}

//--------------------------------------------------
// Description  : Read the IR raw data in fifo
// Input Value  : None
// Output Value : Data ready or not
//--------------------------------------------------
bit ScalerIRHWModeGetData(BYTE *pucBuffer)
{
    ScalerIRHWModeIntHandler_EXINT0();// notice
	
    if(GET_IR_HW_RECEIVED() == _TRUE)
    {
        pucBuffer[0] = g_pucIRCode[0];
        pucBuffer[1] = g_pucIRCode[1];
        pucBuffer[2] = g_pucIRCode[2];
        pucBuffer[3] = g_pucIRCode[3];
        pucBuffer[4] = g_pucIRCode[4];
        pucBuffer[5] = g_pucIRCode[5];
        pucBuffer[6] = g_pucIRCode[6];
        pucBuffer[7] = g_pucIRCode[7];

#if(_DEBUG_MESSAGE_IR == _ON)
        DebugMessageIR("IR0", g_pucIRCode[0]);
        DebugMessageIR("IR1", g_pucIRCode[1]);
        DebugMessageIR("IR2", g_pucIRCode[2]);
        DebugMessageIR("IR3", g_pucIRCode[3]);
        DebugMessageIR("IR4", g_pucIRCode[4]);
        DebugMessageIR("IR5", g_pucIRCode[5]);
        DebugMessageIR("IR6", g_pucIRCode[6]);
        DebugMessageIR("IR7", g_pucIRCode[7]);
#endif // End of #if(_DEBUG_MESSAGE_IR == _ON)

        CLR_IR_HW_RECEIVED();

        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : IR interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeIntHandler_EXINT0(void) using 1
{
    BYTE ucTemp = 0;

    if((ScalerGetBit_EXINT(P23_B2_IR_CR2, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P23_BB_IR_SR3, (_BIT1 | _BIT0)) != 0x00))
    {
        ScalerSetBit_EXINT(P23_BB_IR_SR3, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        if((GET_IR_HW_RECEIVED() == _TRUE) || (ScalerGetBit_EXINT(P23_BB_IR_SR3, (_BIT6 | _BIT5 | _BIT4)) != 0x00))
        {
            // Read out unused code to avoid buffer pointer in disorder
            ucTemp = ScalerGetByte_EXINT(P23_B4_IR_RP0);
            ucTemp = ScalerGetByte_EXINT(P23_B5_IR_RP1);
            ucTemp = ScalerGetByte_EXINT(P23_B6_IR_RP2);
            ucTemp = ScalerGetByte_EXINT(P23_B7_IR_RP3);
            ucTemp = ScalerGetByte_EXINT(P23_DC_IR_RP2_0);
            ucTemp = ScalerGetByte_EXINT(P23_DD_IR_RP2_1);
            ucTemp = ScalerGetByte_EXINT(P23_DE_IR_RP2_2);
            ucTemp = ScalerGetByte_EXINT(P23_DF_IR_RP2_3);

            // Clear error flag
            ScalerSetBit_EXINT(P23_BB_IR_SR3, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
        }
        else
        {
            // Get code
            g_pucIRCode[0] = ScalerGetByte_EXINT(P23_B4_IR_RP0);
            g_pucIRCode[1] = ScalerGetByte_EXINT(P23_B5_IR_RP1);
            g_pucIRCode[2] = ScalerGetByte_EXINT(P23_B6_IR_RP2);
            g_pucIRCode[3] = ScalerGetByte_EXINT(P23_B7_IR_RP3);
            g_pucIRCode[4] = ScalerGetByte_EXINT(P23_DC_IR_RP2_0);
            g_pucIRCode[5] = ScalerGetByte_EXINT(P23_DD_IR_RP2_1);
            g_pucIRCode[6] = ScalerGetByte_EXINT(P23_DE_IR_RP2_2);
            g_pucIRCode[7] = ScalerGetByte_EXINT(P23_DF_IR_RP2_3);

            SET_IR_HW_RECEIVED();
        }
    }
}

//--------------------------------------------------
// Description  : IRDA clock divider switch
// Input Value  : Clock --> _M2PLL_CLK/_EXT_XTAL_CLK(_IOSC_CLK)
// Output Value : None
//--------------------------------------------------
void ScalerIRHWModeClockSel(EnumClkSel enumClock)
{
    if(enumClock == _EXT_XTAL_CLK)
    {
        // HW Sample clock divider
        ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
        ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_XTAL_SAMPLE_CLK_DIV));
    }
    else if(enumClock == _IOSC_CLK)
    {
        // HW Sample clock divider
        ScalerSetByte(P23_AA_IR_SF2, HIBYTE(_IR_HW_IOSC_SAMPLE_CLK_DIV));
        ScalerSetByte(P23_AB_IR_SF3, LOBYTE(_IR_HW_IOSC_SAMPLE_CLK_DIV));
    }
}
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)



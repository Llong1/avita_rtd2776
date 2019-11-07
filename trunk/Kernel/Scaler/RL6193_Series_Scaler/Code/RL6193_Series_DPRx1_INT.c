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
// ID Code      : RL6193_Series_DPRx1_INT.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
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
void ScalerDpRx1CMUNFCodeSetting_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef, EnumDpLinkRate enumLinkRate);
void ScalerDpRx1SetDFEInitial_EXINT0(void);
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx1Tp2SetPhy_EXINT0(void);
void ScalerDpRx1IntHandler_EXINT0(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP CDR N.F. Code Setting
// Input Value  : Link Rate and N.F. Code Clock Ref.
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1CMUNFCodeSetting_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef, EnumDpLinkRate enumLinkRate) using 1
{
    WORD usCMUNCode = 0;
    WORD usCMUFCode = 0;
    WORD usCount = 0;
    DWORD ulFreqDetect = 0;

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        if(enumLinkRate == _DP_LINK_RBR)
        {
            usCMUNCode = 109;
            usCMUFCode = 591;
        }
        else  // HBR HBR2
        {
            usCMUNCode = 184;
            usCMUFCode = 2350;
        }
    }
    else     // Ref. D10.2 Clock
    {
        // [5] ln_ck_sel = 1'b0 -> DP Raw Data
        // [3:0] DP_XTAL_CYCLE = 4'b0011 -> XTAL Counter Cycles = 1000
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), _D1_DP_LANE0);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done -> 50us
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        switch(enumLinkRate)
        {
            case _DP_LINK_HBR2:

                if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usCount = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

                    ulFreqDetect = (((DWORD)usCount * 2700) / 10006) * 100000;

                    usCMUNCode = ((ulFreqDetect / 14318) - 400) / 100;
                    usCMUFCode = (((ulFreqDetect / 14318) - 400) - (usCMUNCode * 100)) * 4096 / 100;
                }
                else
                {
                    usCMUNCode = 184;
                    usCMUFCode = 2350;
                }

                break;

            case _DP_LINK_HBR:

                if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usCount = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

                    ulFreqDetect = (((DWORD)usCount * 2700) / 5003) * 100000;

                    usCMUNCode = ((ulFreqDetect / 14318) - 400) / 100;
                    usCMUFCode = (((ulFreqDetect / 14318) - 400) - (usCMUNCode * 100)) * 4096 / 100;
                }
                else
                {
                    usCMUNCode = 184;
                    usCMUFCode = 2350;
                }

                break;

            case _DP_LINK_RBR:
            default:

                if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
                {
                    usCount = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

                    ulFreqDetect = (((DWORD)usCount * 1620) / 3002) * 100000;

                    usCMUNCode = ((ulFreqDetect / 14318) - 400) / 100;
                    usCMUFCode = (((ulFreqDetect / 14318) - 400) - (usCMUNCode * 100)) * 4096 / 100;
                }
                else
                {
                    usCMUNCode = 109;
                    usCMUFCode = 591;
                }

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // [5] N_CODE[8]
    ScalerSetBit_EXINT(PB0_F1_SDM_00, ~_BIT5, ((usCMUNCode >> 3) & _BIT5));

    // [7:0] N_CODE[7:0]
    ScalerSetByte_EXINT(PB0_F2_SDM_01, (BYTE)usCMUNCode);

    // [4:1] F_CODE[11:8]
    ScalerSetBit_EXINT(PB0_F1_SDM_00, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), ((usCMUFCode >> 7) & (_BIT4 | _BIT3 | _BIT2 | _BIT1)));

    // [7:0] F_CODE[7:0]
    ScalerSetByte_EXINT(PB0_F3_SDM_02, (BYTE)usCMUFCode);
}

//--------------------------------------------------
// Description  : DP PHY DFE Initial Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1SetDFEInitial_EXINT0(void) using 1
{
    // [7] Positive Symbol-Rate Clock
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P7A_A0_L0_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_B0_L1_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_C0_L2_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_D0_L3_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));

    // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 2)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P7A_E0_MODE_TIMER, 0xB2);

    // Set DFE Delay Time
    ScalerSetByte_EXINT(P7A_E1_TIMER, 0x01);

    // Tap0,Tap1 Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap2,Tap3 Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap4,Servo Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // LE Gain1 Loop Gain 1/256, LE Gain2 Loop Gain 0, LE Pre-Courser Gain 0
    ScalerSetBit_EXINT(P7A_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT4 | _BIT3));
    ScalerSetBit_EXINT(P7A_FA_GAIN_PREC, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap5,Tap6 Loop Gain 1/512
    ScalerSetBit_EXINT(P7A_F7_GAIN_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));

    // Tap0 Max is 21
    ScalerSetByte_EXINT(P7A_E6_LIMIT_1, 0x35);

    // Tap1 Min is 31
    ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT4 | _BIT3));

    // Tap4 Max is 0, Min is -3
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Tap0 Threshold
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 0
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x62);
    }

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P7A_EC_LOOP_DIV_1, 0xA3);

    if(g_ucDpRx1TrainingPatternSet == _DP_TRAINING_PATTERN_3)
    {
        // Tap Divider = 34 for TP3
        ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xE2);
    }
    else
    {
        // Tap Divider = 10 for TP2
        ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xCA);
    }

    // [5] servo_notrans = 1'b0 --> Servo is Effective Each Bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective Each Bit
    ScalerSetBit_EXINT(P7A_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // LE Max = 15, Initial = 12, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0xFC);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0xFC);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0xFC);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0xFC);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0x10);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0x10);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0x10);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0x10);
    }
    else
    {
        // LE Max = 20, Initial = 12, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0x90);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0x90);
    }

    // Tap0 Initial Value = 12
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, 0x0C);

    // Tap1 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, 0x00);
    ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, 0x00);
    ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, 0x00);
    ScalerSetByte_EXINT(P7A_D5_L3_INIT_3, 0x00);

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_C6_L2_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_D6_L3_INIT_4, 0x00);

    // Vth Initial Value = 4
    ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7A_D9_L3_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_DA_L3_INIT_8, 0xFF);
    ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_DC_L3_DFE_EN_3, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_DA_L3_INIT_8, 0x00);
    ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit_EXINT(P7A_DC_L3_DFE_EN_3, ~(_BIT5 | _BIT4), 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_DC_L3_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP1
// Input Value  : FLD Reference Clock
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef) using 1
{
    ///////////////////////////
    // RX CMU EN & Mac Power //
    ///////////////////////////

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, 0x00);

    // Disable RX_EN, CDR_EN
    ScalerSetByte_EXINT(PB0_A1_CMU_01, 0x00);

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~_BIT4, _BIT4);

            // Enable Local Bias LPF
            ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT5, _BIT5);

            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~_BIT0, _BIT0);

            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

            // Enable Local Bias LPF
            ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT5, _BIT5);

            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // Enable Local Bias LPF
            ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT5, _BIT5);

            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }


    /////////////////
    // CMU Setting //
    /////////////////

    // [5] CMU_BYPASS_PI = 1'b0 --> Fractional N PLL
    ScalerSetBit_EXINT(PB0_A5_CMU_05, ~_BIT5, 0x00);

    // [7] BYPASS_PI = 1'b0 --> Use Fractional N_F_CODE
    ScalerSetBit_EXINT(PB0_F1_SDM_00, ~_BIT7, 0x00);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:5] rate_sel = 3'b000 --> 5.4GHz
            ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] SEL_DIV = 3'b000 --> 5.4GHz
            // [4:2] CMU_PI_I_SEL = 3'b011 --> 12.5uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x0C);

            // [7:4] CMU_SEL_PUMP_I = 4'b1100 --> Icp = 35uA
            // [3:1] CMU_SEL_RI = 3'b000 --> Rs = 6KOhm
            // [0] CMU_SEL_CP = 1'b0 --> Cp = 1pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0xC0);

            // [5] CMU_BYPASS_PI = 1'b1 --> Integer N PLL
            ScalerSetBit_EXINT(PB0_A5_CMU_05, ~_BIT5, _BIT5);

            // [7] BYPASS_PI = 1'b1 --> Use Integer N Code
            ScalerSetBit_EXINT(PB0_F1_SDM_00, ~_BIT7, _BIT7);

            // Digital CDR Ref Clock = Analog CDR / 20
            ScalerSetBit_EXINT(PB0_AE_CDR_05, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT1, _BIT1);

            // [7:0] N_CODE = 8'b0001 0000 --> 16 + 4 = 20
            ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x10);

            break;

        case _DP_LINK_HBR:

            // [7:5] rate_sel = 3'b001 --> 2.7GHz
            ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // [7:5] SEL_DIV = 3'b001 --> 2.7GHz
            // [4:2] CMU_PI_I_SEL = 3'b011 --> 12.5uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x2C);

            // [7:4] CMU_SEL_PUMP_I = 4'b0101 --> Icp = 15uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b0 --> Cp = 1pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x56);

            // [5] CMU_BYPASS_PI = 1'b0 --> Fractional N PLL
            ScalerSetBit_EXINT(PB0_A5_CMU_05, ~_BIT5, 0x00);

            // [7] BYPASS_PI = 1'b0 --> Use Fractional N_F_CODE
            ScalerSetBit_EXINT(PB0_F1_SDM_00, ~_BIT7, 0x00);

            ScalerDpRx1CMUNFCodeSetting_EXINT0(enumDpNFCodeRef, _DP_LINK_HBR);

            break;

        case _DP_LINK_RBR:
        default:

            // [7:5] rate_sel = 3'b001 --> 1.62GHz
            ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // [7:5] SEL_DIV = 3'b001 --> 1.62GHz
            // [4:2] CMU_PI_I_SEL = 3'b011 --> 12.5uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x2C);

            // [7:4] CMU_SEL_PUMP_I = 4'b0101 --> Icp = 15uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b0 --> Cp = 1pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x56);

            // [5] CMU_BYPASS_PI = 1'b0 --> Fractional N PLL
            ScalerSetBit_EXINT(PB0_A5_CMU_05, ~_BIT5, 0x00);

            // [7] BYPASS_PI = 1'b0 --> Use Fractional N_F_CODE
            ScalerSetBit_EXINT(PB0_F1_SDM_00, ~_BIT7, 0x00);

            ScalerDpRx1CMUNFCodeSetting_EXINT0(enumDpNFCodeRef, _DP_LINK_RBR);

            break;
    }


    /////////////////////
    // A/D CDR Setting //
    /////////////////////

    // [3:0] KD = 4'b0000 --> KD = 0
    ScalerSetBit_EXINT(PB0_CC_ERROR_COUNT_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR2:

            // [5:4] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 550M/v
            ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~(_BIT5 | _BIT4), _BIT4);

            // [4:2] reg_sel_cdr_res = 3'b011 --> Analog CDR Rs = 4K
            ScalerSetBit_EXINT(PB0_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            // [3:0] reg_cdr_cp_in = 4'b0011 --> Analog CDR Icp = 10.5uA
            ScalerSetBit_EXINT(PB0_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            // KI = 3'b000 --> KI = 0
            ScalerSetByte_EXINT(PB0_D4_KI_0, 0x00);
            ScalerSetByte_EXINT(PB0_D5_KI_1, 0x00);

            // KP = 0x07 --> KP = 1.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x07);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x07);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x07);
            ScalerSetByte_EXINT(PB0_D9_KP_3, 0x07);

            break;

        case _DP_LINK_HBR:

            // KI = 3'b010 --> KI = 1/8
            ScalerSetByte_EXINT(PB0_D4_KI_0, 0x48);
            ScalerSetByte_EXINT(PB0_D5_KI_1, 0x48);

            // KP = 0x1F --> KP = 7.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x1F);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x1F);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x1F);
            ScalerSetByte_EXINT(PB0_D9_KP_3, 0x1F);

            break;

        case _DP_LINK_RBR:
        default:

            // KI = 3'b010 --> KI = 1/8
            ScalerSetByte_EXINT(PB0_D4_KI_0, 0x48);
            ScalerSetByte_EXINT(PB0_D5_KI_1, 0x48);

            // KP = 0x37 --> KP = 13.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x37);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x37);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x37);
            ScalerSetByte_EXINT(PB0_D9_KP_3, 0x37);

            break;
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // Disable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB0_F7_DATA_TIMER, ~_BIT0, 0x00);

    // Disable Hybrid Mode
    ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, 0x00);

    // [3:0] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB0_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [3:0] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB0_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));


    /////////////////
    // DFE Setting //
    /////////////////

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR2:

            // [7:5] LE_ISEL = 3'b011
            // [4:2] LE_RLSEL = 3'b000
            ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;

        case _DP_LINK_HBR:

            // [7:5] LE_ISEL = 3'b010
            // [4:2] LE_RLSEL = 3'b001
            ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));

            break;

        case _DP_LINK_RBR:
        default:

            // [7:5] LE_ISEL = 3'b000
            // [4:2] LE_RLSEL = 3'b011
            ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;
    }


    //////////////
    // K Offset //
    //////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB0_B0_CDR_07, ~_BIT1, 0x00);

    // [2] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB0_AD_CDR_04, ~_BIT2, _BIT2);

    // [5] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, _BIT5);

    // Waiting for K Offset
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, _BIT7);

    // Enable Tap1/2
    ScalerSetBit_EXINT(PB0_B2_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [4] reg_en_data_manual_l0 = 1'b0
        // [3] reg_bypass_data_rdy_l0 = 1'b0
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), 0x00);

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT5, 0x00);

        // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT4, _BIT4);

        // [0] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~_BIT0, _BIT0);

        // [6] reg_xtal_en = 1'b0 --> Using D10.2
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT6, 0x00);

        // Analog CDR Auto FLD Counter
        ScalerSetByte_EXINT(PB0_FA_LANE0_A_CDR_04, 0xF9);
        ScalerSetByte_EXINT(PB0_FB_LANE0_A_CDR_05, 0x7D);
        ScalerSetByte_EXINT(PB0_FC_LANE0_A_CDR_06, 0x85);

        // [7] reg_en_ana_cdr = 1'b1 --> Enable Analog CDR
        // [6] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
        // [3] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
        // [2] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
        // [1] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
        // [0] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3));
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT0, _BIT0);

        // Enable Lane0 the LE, Vth, Tap0~1 Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);

        // Waiting for FLD Lock Band
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // Enable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, _BIT0);
    }
    else
    {
        // [7] reg_en_ana_cdr = 1'b0 --> Disable Analog CDR
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT7, 0x00);

        // [0] reg_acdr_l0_en = 1'b0 --> Disable Lane0 ACDR
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~_BIT0, 0x00);
    }

    // Enable Vth/Tap0 Adaptation
    ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_DC_L3_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);

    // Reset Digital CDR
    ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x00);
    ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x78);

    // Waiting for CMU PLL Stable
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

    // [0] en_eqen_manual = 1 --> Enable Adapation
    ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, _BIT0);

    // Waiting for DFE Adaptation
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // Start to Record Tap0 Max/Min
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

    // Waiting for DFE Adaptation
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // Stop To Record Tap0 Max/Min
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

    // Disable All Adapation Loop
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

    // Reload Tap0
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);

    // [0] en_eqen_manual = 1'b0 --> Disable Adaptation for Digital CDR
    ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB0_F7_DATA_TIMER, ~_BIT0, _BIT0);

    if(ScalerGetBit_EXINT(PB0_FF_LANE0_A_CDR_09, _BIT0) == _BIT0)
    {
        // [5] reg_adp_eq_off = 1'b1 --> Disable Adaptation for Analog CDR
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT5, _BIT5);

        // [4] reg_en_data_manual_l0 = 1'b1
        // [3] reg_bypass_data_rdy_l0 = 1'b1
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // [5] ln_ck_sel = 1'b0 -> DP Raw Data
        // [3:0] DP_XTAL_CYCLE = 4'b0011 -> XTAL Counter Cycles = 1000
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
        ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), 0x00);

        // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
        ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

        // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

        // Waiting for Measure Done -> 50us
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            g_usDpRx1ClockCount = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));
        }
        else
        {
            g_usDpRx1ClockCount = 0x2710;
        }

        // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
        ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    }

    // DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp2SetPhy_EXINT0(void) using 1
{
    BYTE ucBestVCOBand = 0;
    WORD usVCOBandDiff = 0xFFFF;
    BYTE ucTemp = 0;

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, 0x00);

    // Enable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // Enable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // Disable Enhancement Control Mode --> MAC
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB0_F7_DATA_TIMER, ~_BIT0, 0x00);

    // Disable Hybrid Mode
    ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, 0x00);

    // [3:0] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB0_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [3:0] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB0_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, _BIT7);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [4] transition_only = 1'b1 --> LE/Tap1/2 Effective Only in Transition Bit
        ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~_BIT4, _BIT4);

        // [4] reg_en_data_manual_l0 = 1'b0
        // [3] reg_bypass_data_rdy_l0 = 1'b0
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), 0x00);

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // [3] reg_cp_en_manual = 1'b0 -->  Disable cp_en_manual
        // [2] reg_adp_en_manual = 1'b0 --> Disable adp_en_manual
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~(_BIT3 | _BIT2), 0x00);

        // [4] reg_auto_mode = 1'b0 --> FLD Manual Mode
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT4, 0x00);

        // [0] en_clkout_manual = 1'b1 --> Enable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

        // [2] reg_adp_en_manual = 1'b1 --> Enable adp_en_manual
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT2, _BIT2);

        ucBestVCOBand = ScalerGetByte_EXINT(PB0_BF_LANE0_A_CDR_02);

        for(ucTemp = 0; ucTemp <= 5; ucTemp++)
        {
            // Manually Reload FLD Band
            ScalerSetByte_EXINT(PB0_BE_LANE0_A_CDR_01, (ScalerGetByte_EXINT(PB0_BF_LANE0_A_CDR_02) - 2 + ucTemp));

            // Waiting for VCO Stable
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            // [5] ln_ck_sel = 1'b1 -> CDR Clock
            // [3:0] DP_XTAL_CYCLE = 4'b0011 -> XTAL Counter Cycles = 1000
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

            // [1:0] freqdet_lane_sel = 2'b00 -> Lane0
            ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), 0x00);

            // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
            ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

            // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

            // Waiting for Measure Done -> 50us
            for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
            {
                g_usDpRx1ClockCount1 = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));
            }
            else
            {
                ucBestVCOBand = ScalerGetByte_EXINT(PB0_BF_LANE0_A_CDR_02);
                continue;
            }

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            if(abs(g_usDpRx1ClockCount1 - g_usDpRx1ClockCount) < usVCOBandDiff)
            {
                usVCOBandDiff = abs(g_usDpRx1ClockCount1 - g_usDpRx1ClockCount);
                ucBestVCOBand = (ScalerGetByte_EXINT(PB0_BF_LANE0_A_CDR_02) - 2 + ucTemp);
            }
        }

        // Manually Reload FLD Band
        ScalerSetByte_EXINT(PB0_BE_LANE0_A_CDR_01, ucBestVCOBand);

        // Waiting for VCO Stable
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [3] reg_cp_en_manual = 1'b1 -->  Enaable cp_en_manual
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT3, _BIT3);

        // Enable Tap0 Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x01);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop To Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable Tap0 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back Tap0 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

        g_pucDpRx1Tap0MaxTemp[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Tap0 Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Reload Max Value of Tap0 (Lane0)
        ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, g_pucDpRx1Tap0MaxTemp[0]);

        // Reload Tap0
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);

        // Enable LE Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x80);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop To Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable LE Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // Reload LE Min (Lane0)
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucDpRx1LEMinTemp[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucDpRx1LEMaxTemp[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        g_ucDpRx1Temp = 0;

        if(g_pucDpRx1LEMaxTemp[g_ucDpRx1Temp] > g_pucDpRx1LEMinTemp[g_ucDpRx1Temp])
        {
            if(g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] < 10)
            {
                g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] = g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] + 2;
            }
            else if(g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] < 12)
            {
                g_pucDpRx1LEMinTemp[g_ucDpRx1Temp]++;
            }
        }

        // Reload LE to Min
        ScalerSetBit_EXINT(P7A_A2_L0_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_A3_L0_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[0] << 2) & _BIT6));

        // Reload LE
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT7, 0x00);

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // Enable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, _BIT0);

        // Enable Tap0 Adaptation
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x01);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x01);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x01);

        // Reset Digital CDR
        ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x00);
        ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x78);

        // Waiting for CMU PLL Stable
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

        // [0] en_eqen_manual = 1 --> Enable Adapation
        ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop To Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adapation Loop
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back Tap0 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

        g_pucDpRx1Tap0MaxTemp[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back Tap0 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

        g_pucDpRx1Tap0MaxTemp[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane3
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back Tap0 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

        g_pucDpRx1Tap0MaxTemp[3] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Reload Max Value of Tap0 (Lane1)
        ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, g_pucDpRx1Tap0MaxTemp[1]);

        // Reload Max Value of Tap0 (Lane2)
        ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, g_pucDpRx1Tap0MaxTemp[2]);

        // Reload Max Value of Tap0 (Lane3)
        ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, g_pucDpRx1Tap0MaxTemp[3]);

        // Reload Tap0 Max
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);

        // Enable LE Adaptation
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x80);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x80);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x80);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop To Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adapation Loop
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucDpRx1LEMinTemp[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucDpRx1LEMaxTemp[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucDpRx1LEMinTemp[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucDpRx1LEMaxTemp[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane3
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucDpRx1LEMinTemp[3] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucDpRx1LEMaxTemp[3] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        for(g_ucDpRx1Temp = 1; g_ucDpRx1Temp <= 3; g_ucDpRx1Temp++)
        {
            if(g_pucDpRx1LEMaxTemp[g_ucDpRx1Temp] > g_pucDpRx1LEMinTemp[g_ucDpRx1Temp])
            {
                if(g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] < 10)
                {
                    g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] = g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] + 2;
                }
                else if(g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] < 12)
                {
                    g_pucDpRx1LEMinTemp[g_ucDpRx1Temp]++;
                }
            }
        }

        // Reload LE to Min
        ScalerSetBit_EXINT(P7A_B2_L1_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_B3_L1_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[1] << 2) & _BIT6));

        // Reload LE to Min
        ScalerSetBit_EXINT(P7A_C2_L2_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_C3_L2_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[2] << 2) & _BIT6));

        // Reload LE to Min
        ScalerSetBit_EXINT(P7A_D2_L3_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_D3_L3_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[3] << 2) & _BIT6));

        // Reload LE
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT7, 0x00);

        // Enable Tap0/1 Adapt
        ScalerSetBit_EXINT(P7A_A1_L0_DFE_EN_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_B1_L1_DFE_EN_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_C1_L2_DFE_EN_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_D1_L3_DFE_EN_2, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record DFE Coef.
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 20; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record DFE Coef.
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable Tap0/1 Adapt
        ScalerSetBit_EXINT(P7A_A1_L0_DFE_EN_2, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_B1_L1_DFE_EN_2, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_C1_L2_DFE_EN_2, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_D1_L3_DFE_EN_2, ~(_BIT1 | _BIT0), 0x00);


        ///////////
        // Lane0 //
        ///////////

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        g_pucDpRx1Tap1MaxTemp[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);


        ///////////
        // Lane1 //
        ///////////

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        g_pucDpRx1Tap1MaxTemp[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);


        ///////////
        // Lane2 //
        ///////////

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        g_pucDpRx1Tap1MaxTemp[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);


        ///////////
        // Lane3 //
        ///////////

        // Read Back Lane3
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        g_pucDpRx1Tap1MaxTemp[3] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 3; g_ucDpRx1Temp++)
        {
            if(g_pucDpRx1Tap1MaxTemp[g_ucDpRx1Temp] > 10)
            {
                g_pucDpRx1Tap1MaxTemp[g_ucDpRx1Temp] = 0x06;

                if(g_pucDpRx1LEMinTemp[g_ucDpRx1Temp] < 15)
                {
                    g_pucDpRx1LEMinTemp[g_ucDpRx1Temp]++;
                }
            }
        }

        // Reload LE
        ScalerSetBit_EXINT(P7A_A2_L0_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_A3_L0_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[0] << 2) & _BIT6));
        ScalerSetBit_EXINT(P7A_B2_L1_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_B3_L1_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[1] << 2) & _BIT6));
        ScalerSetBit_EXINT(P7A_C2_L2_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_C3_L2_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[2] << 2) & _BIT6));
        ScalerSetBit_EXINT(P7A_D2_L3_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucDpRx1LEMinTemp[3] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_D3_L3_INIT_1, ~_BIT6, ((g_pucDpRx1LEMinTemp[3] << 2) & _BIT6));

        // Reload Max Value of Tap0
        ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, g_pucDpRx1Tap0MaxTemp[0]);
        ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, g_pucDpRx1Tap0MaxTemp[1]);
        ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, g_pucDpRx1Tap0MaxTemp[2]);
        ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, g_pucDpRx1Tap0MaxTemp[3]);

        // Reload Tap1
        ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, g_pucDpRx1Tap1MaxTemp[0]);
        ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, g_pucDpRx1Tap1MaxTemp[1]);
        ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, g_pucDpRx1Tap1MaxTemp[2]);
        ScalerSetByte_EXINT(P7A_D5_L3_INIT_3, g_pucDpRx1Tap1MaxTemp[3]);

        // Load LE/Tap0/Tap1
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~(_BIT7 | _BIT1 | _BIT0), 0x00);

        // [4] transition_only = 1 --> Each Bit is Effective
        ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~_BIT4, 0x00);

        // Enable Tap 3/4 Adapt
        ScalerSetBit_EXINT(P7A_A1_L0_DFE_EN_2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit_EXINT(P7A_B1_L1_DFE_EN_2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit_EXINT(P7A_C1_L2_DFE_EN_2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
        ScalerSetBit_EXINT(P7A_D1_L3_DFE_EN_2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
    else
    {
        // [4] transition_only = 1'b1 --> LE/Tap1/2 Effective Only in Transition Bit
        ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~_BIT4, _BIT4);

        // Enable Tap0/Vth/LE/Tap1/Tap2 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xC7);

        // Reset Digital CDR
        ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x00);
        ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x78);

        // Waiting for CMU PLL Stable
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [0] en_clkout_manual = 1 --> Enable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

        // [0] en_eqen_manual = 1 --> Enable Adapation
        ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 40; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Only Enable Vth/Tap0 Adapation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);

        // Set Vth Min = 0
        ScalerSetBit_EXINT(P7A_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB0_F7_DATA_TIMER, ~_BIT0, _BIT0);

    if(ScalerGetBit_EXINT(PB0_FF_LANE0_A_CDR_09, _BIT0) == _BIT0)
    {
        // [4] reg_en_data_manual_l0 = 1'b1
        // [3] reg_bypass_data_rdy_l0 = 1'b1
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }
}

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1IntHandler_EXINT0(void) using 1
{
    WORD usDPCDAddress = 0;

    if(ScalerGetBit_EXINT(PBA_7A_AUX_DIG_PHYA, (_BIT4 | _BIT0)) == (_BIT4 | _BIT0))
    {
        if(ScalerGetBit_EXINT(PBA_79_AUX_DIG_PHY9, (_BIT3 | _BIT2 | _BIT1 | _BIT0)) == 0x00)
        {
            if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
            {
                MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
            }

            // Disable Aux INT
            ScalerSetBit_EXINT(PBA_7A_AUX_DIG_PHYA, ~_BIT4, 0x00);

            // Enable GDI BandGap
            ScalerSetBit_EXINT(PB_B4_BANDGAP_00, ~_BIT7, _BIT7);

            // Disable Aux Power Saving Mode
            ScalerSetBit_EXINT(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit_EXINT(PBA_63_AUX_3, ~_BIT7, 0x00);

            // Aux comm current select max
            ScalerSetBit_EXINT(PBA_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            SET_DP_RX1_PS_AUX_TOGGLE();

            IP = 0xA0;

            return;
        }
        else
        {
            // Clear Aux INT flag
            ScalerSetBit_EXINT(PBA_7A_AUX_DIG_PHYA, ~_BIT0, _BIT0);

            // Clear Manchester/Stop pattern/Sync_end pattern/Byte boundary check Error
            ScalerSetBit_EXINT(PBA_79_AUX_DIG_PHY9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            return;
        }
    }

#if(_D0_INPUT_PORT_TYPE != _D0_DP_PORT)
#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
    if((ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7) &&
       (ScalerGetBit_EXINT(PBA_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) &&
       (GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN() == _FALSE))
    {
        // Detect if Aksv(0x6800B) is Written by Source
        if((ScalerGetByte_EXINT(PBA_D3_AUX_RX_ADDR_M) == 0x80) && (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L) == 0x0C))
        {
            SET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
        }
    }
#endif
#endif

    if(ScalerGetBit_EXINT(PBA_D0_AUX_MODE_SET, _BIT1) == _BIT1)
    {
        // Aux Firmware Control -> Reply Defer
        SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
    }

    g_pucDpRx1Backup[0] = ScalerGetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H);
    g_pucDpRx1Backup[1] = ScalerGetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M);
    g_pucDpRx1Backup[2] = ScalerGetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L);

    // DP Global IRQ Flag
    if(ScalerGetBit_EXINT(PBA_DC_AUX_IRQ_STATUS, _BIT7) == _BIT7)
    {
        if((MCU_FFED_MCU_CONTROL & _BIT1) == 0x00)
        {
            MCU_FFE9_MCU_CLK_CONTROL_1 = (_FLASH_CLK_PS_FAST_DIV | (MCU_FFE9_MCU_CLK_CONTROL_1 & 0xF0));
        }

        // DPCD 0x2002 Into INT
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
        {
            // CLR Flag
            ScalerSetByte_EXINT(PBA_FB_DUMMY_1, 0xC0);
            ScalerSetByte_EXINT(PBA_FB_DUMMY_1, 0x40);

#if(_DP_TX_SUPPORT == _ON)

            if(GET_DP_RX1_POWER_STATE_INTO_PS() == _TRUE)
            {
                SET_DP_RX1_AUX_COMMAND_NO_REPLY();
            }
            else
#endif
            {
                if(ScalerGetByte_EXINT(PBA_D2_AUX_RX_CMD) == 0x90)
                {
                    usDPCDAddress = (((WORD)(ScalerGetByte_EXINT(PBA_D3_AUX_RX_ADDR_M)) << 8) | ((WORD)(ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L)) & 0x00FF));

                    // Reset Aux FIFO
                    ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);

                    pData_EXINT[1] = (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F) + 1;
                    usDPCDAddress -= pData_EXINT[1];

                    for(pData_EXINT[0] = 0; pData_EXINT[0] < pData_EXINT[1]; pData_EXINT[0]++)
                    {
                        if((usDPCDAddress + pData_EXINT[0]) == 0x2002)
                        {
                            ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x00));
                        }
                        else
                        {
                            ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, (BYTE)((usDPCDAddress + pData_EXINT[0]) >> 8), (BYTE)((usDPCDAddress + pData_EXINT[0]) & 0x00FF)));
                        }
                    }

                    ScalerSetByte_EXINT(PBA_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F));

                    // Only Reply when State Machine is at Transmit Idle Standby State
                    if(ScalerGetBit_EXINT(PBA_C7_TP1_OCCR, 0x07) == 0x02)
                    {
                        ScalerSetByte_EXINT(PBA_D7_AUX_TX_CMD, 0x00);
                    }
                }
            }
        }

        // Fifo overflow/ underflow IRQ & flag
        if((ScalerGetBit_EXINT(PB9_3A_DP_IRQ_CTRL0, (_BIT1 | _BIT0)) != 0x00) && (ScalerGetBit_EXINT(PB8_21_PG_CTRL_1, (_BIT4 | _BIT2)) != 0x00))
        {
            // Disable fifo overflwo/ underflwo IRQ
            ScalerSetBit_EXINT(PB9_3A_DP_IRQ_CTRL0, ~(_BIT1 | _BIT0), 0x00);

            if(GET_DP_RX1_FORCE_BCKGRD_PATH() != _DISPLAY_PATH_NONE)
            {
                // Set free run
                ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT3, 0x00);

                if((GET_DP_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M1) != 0)
                {
                    // Set Display M1 output force to background color and free run mode
                    ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
                }

                if((GET_DP_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M2) != 0)
                {
                    // Set Display M2 output force to background color and free run mode
                    ScalerSetBit_EXINT(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, ~_BIT5, _BIT5);
                }

                if((GET_DP_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S1) != 0)
                {
                    // Set Display S1 output force to background color and free run mode
                    ScalerSetBit_EXINT(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, ~_BIT5, _BIT5);
                }

                if((GET_DP_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S2) != 0)
                {
                    // Set Display S2 output force to background color and free run mode
                    ScalerSetBit_EXINT(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, ~_BIT5, _BIT5);
                }
            }

            // The Judge Handler take much time, It lead to MacBook 720P @50 <---> @60 Timing changing Issue
            if(((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x11) & _BIT0) == 0x00) &&
               (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0) &&
               (ScalerDpRx1DFECheck_EXINT0() == _FALSE))
            {
                // ScalerTimerWDActivateTimerEvent_EXINT0(200, _SCALER_WD_TIMER_EVENT_RX1_DP_LINK_STATUS_FAIL);

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x04, 0x80);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x05, 0x00);
            }
        }

        if((ScalerGetByte_EXINT(PBA_DD_AUX_DPCD_IRQ) & (_BIT7 | _BIT6 | _BIT5)) != 0x00) // Write Link Config Field into INT0
        {
            g_ucDpRx1TrainingPatternSet = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x02) & 0x03);

            // SVN Record 1167
            if(((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)) &&
               ((ScalerGetByte_EXINT(PBA_DD_AUX_DPCD_IRQ) & (_BIT7 | _BIT6 | _BIT5)) == _BIT6) &&
               ((g_ucDpRx1LinkRate != ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x00)) ||
                (g_ucDpRx1LaneCount != (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F))))
            {
                g_ucDpRx1TrainingPatternSet = _DP_TRAINING_PATTERN_END;

                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_NONE);
            }

            g_ucDpRx1LinkRate = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x00);
            g_ucDpRx1LaneCount = (ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & 0x1F);

            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            switch(g_ucDpRx1TrainingPatternSet)
            {
                case _DP_TRAINING_PATTERN_1:

#if(_DP_MST_SUPPORT == _ON)
                    CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();
#endif

                    if(GET_DP_RX1_FAKE_LINK_TRAINING() == _FALSE)
                    {
                        if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_NORMAL_TRAINING_PATTERN_1_PASS)
                        {
                            if(ScalerDpRx1TrainingPattern1_EXINT0(_DP_NORMAL_LT) == _TRUE)
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }
                    else
                    {
                        if(GET_DP_RX1_LINK_TRAINING_STATUS() != _DP_FAKE_TRAINING_PATTERN_1_PASS)
                        {
                            if(ScalerDpRx1TrainingPattern1_EXINT0(_DP_FAKE_LT) == _TRUE)
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_PASS);
                            }
                            else
                            {
                                SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_1_FAIL);
                            }
                        }
                    }

                    break;

                case _DP_TRAINING_PATTERN_2:
                case _DP_TRAINING_PATTERN_3:

                    if((GET_DP_RX1_FAKE_LINK_TRAINING() == _FALSE) &&
                       ((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                        (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL)))
                    {
                        if(ScalerDpRx1TrainingPattern2_EXINT0(_DP_NORMAL_LT) == _TRUE)
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_PASS);

                            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), 0x00);
                        }
                        else
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_NORMAL_TRAINING_PATTERN_2_FAIL);
                        }
                    }
                    else if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_PASS) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL))
                    {
                        if(ScalerDpRx1TrainingPattern2_EXINT0(_DP_FAKE_LT) == _TRUE)
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_PASS);
                        }
                        else
                        {
                            SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_TRAINING_PATTERN_2_FAIL);
                        }
                    }

                    break;

                case _DP_TRAINING_PATTERN_END:

                    // ScalerTimerWDCancelTimerEvent_EXINT0(_SCALER_WD_TIMER_EVENT_RX1_DP_LINK_STATUS_FAIL);

                    ScalerDpRx1TrainingPatternEnd_EXINT0();

                    if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_PASS) || (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_PASS))
                    {
                        ScalerDpRx1SetDpcdBitValue_EXINT0(0x00, 0x06, 0x00, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

                        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_FAKE_LINK_TRAINING_PASS);

                        // Set DP Receive Port0 In Sync
                        ScalerDpRx1SinkStatusSet_EXINT0(_DP_SINK_REVEICE_PORT0, _DP_SINK_IN_SYNC);

                        // Aux Hardware Control
                        ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, _BIT1);

                        // DP Mac Reset
                        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, _BIT1);
                        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);
                    }
                    else if((GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_NORMAL_TRAINING_PATTERN_2_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_1_FAIL) ||
                            (GET_DP_RX1_LINK_TRAINING_STATUS() == _DP_FAKE_TRAINING_PATTERN_2_FAIL))
                    {
                        SET_DP_RX1_LINK_TRAINING_STATUS(_DP_LINK_TRAINING_FAIL);
                    }

                    break;

                default:
                    break;
            }
        }

        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT0) == _BIT0) // Write 00600h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT0, _BIT0);

            if((ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT1) ||
               (ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == (_BIT2 | _BIT0)))
            {
                // DP Power Down
#if(_DP_MST_SUPPORT == _ON)
                SET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();

                g_pucDpRx1LinkStatusBackup_INT[0] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x02);
                g_pucDpRx1LinkStatusBackup_INT[1] = ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x02, 0x03);

                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, 0x00);
                ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, 0x00);
#endif
            }
            else if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x06, 0x00, (_BIT2 | _BIT1 | _BIT0)) == _BIT0)
            {
                // DP Power Normal
#if(_DP_MST_SUPPORT == _ON)
                if(GET_DP_RX1_BACKUP_PD_LINK_STATUS_FLG() == _TRUE)
                {
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x02, g_pucDpRx1LinkStatusBackup_INT[0]);
                    ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x03, g_pucDpRx1LinkStatusBackup_INT[1]);
                }

                CLR_DP_RX1_BACKUP_PD_LINK_STATUS_FLG();
                g_pucDpRx1LinkStatusBackup_INT[0] = 0X00;
                g_pucDpRx1LinkStatusBackup_INT[1] = 0X00;
#endif
            }
        }

        if(ScalerGetBit_EXINT(PBA_DA_AUX_FIFO_RST, (_BIT2 | _BIT1)) == (_BIT2 | _BIT1)) // Write 68xxxh into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT1, _BIT1);

            // Clear Integrity Failure Flag
            ScalerSetBit_EXINT(PB0_1B_HDCP_INTGT_VRF, ~_BIT1, _BIT1);

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
            // Detect if Aksv(0x6800B) is Written by Source
            if(GET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN() == _TRUE)
            {
                ScalerDpRx1HDCPResetDpcdInfo_EXINT0();
            }

            if(ScalerGetBit_EXINT(PBA_FA_DUMMY_0, _BIT3) == _BIT3)
            {
                // Detect if V'(0x68027) is read by Source
                if((ScalerGetByte_EXINT(PBA_D3_AUX_RX_ADDR_M) == 0x80) && (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L) == 0x28))
                {
                    ScalerDpRx1HDCPResetKsvFifoToFirst_EXINT0();
                }
            }
#endif
            if(GET_DP_RX1_FAKE_LINK_TRAINING() == _TRUE)
            {
                // DP Mac Clock Select to Xtal Clock
                ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, _BIT6);
            }
        }

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))

        // Read 6803A into INT0
        if(ScalerGetBit_EXINT(PBA_FA_DUMMY_0, (_BIT1 | _BIT0)) == (_BIT1 | _BIT0))
        {
            CLR_DP_RX1_HDCP_KSV_FIFO_INT_FLAG_EXINT();

            ScalerDpRx1HDCPSetKsvFifo_EXINT0();
        }

#endif

        if(ScalerGetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, _BIT2) == _BIT2) // Write 00270h into INT0
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_DD_AUX_DPCD_IRQ, ~_BIT2, _BIT2);

            if(ScalerDpRx1GetDpcdBitInfo_EXINT0(0x00, 0x02, 0x70, _BIT0) == _BIT0)
            {
                SET_DP_RX1_CRC_CALCULATE();
            }

            // Clear TEST_CRC_COUNT
            ScalerDpRx1SetDpcdValue_EXINT0(0x00, 0x02, 0x46, 0x20);
        }
    }

#if(_DP_MST_SUPPORT == _ON)
    ScalerDpRxMstIntHandle_EXINT0();
#endif

    ScalerSetByte_EXINT(PBA_C1_DPCD_ADDR_PORT_H, g_pucDpRx1Backup[0]);
    ScalerSetByte_EXINT(PBA_C2_DPCD_ADDR_PORT_M, g_pucDpRx1Backup[1]);
    ScalerSetByte_EXINT(PBA_C3_DPCD_ADDR_PORT_L, g_pucDpRx1Backup[2]);
}
#endif // End of if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)

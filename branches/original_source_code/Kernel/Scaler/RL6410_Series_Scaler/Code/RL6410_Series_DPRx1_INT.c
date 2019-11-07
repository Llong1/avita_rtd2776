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
// ID Code      : RL6410_Series_DPRx1_INT.c No.0000
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
void ScalerDpRx1AdjustLaneFLDBand_EXINT0(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff);
void ScalerDpRx1SetDFEInitial_EXINT0(void);
void ScalerDpRx1Tp1SetPhy_EXINT0(EnumDpNFCodeRef enumDpNFCodeRef);
void ScalerDpRx1Tp2SetPhy_EXINT0(void);
void ScalerDpRx1IntHandler_EXINT0(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP FLD Band Finetune
// Input Value  : LaneNumber
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1AdjustLaneFLDBand_EXINT0(BYTE ucDpRx1LaneNumber, WORD usVCOBandDiff) using 1
{
    BYTE ucBestVCOBand = 0;
    BYTE ucAutoVCOBand = 0;

    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F);

            break;

        case _DP_SCALER_LANE1:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F);

            break;

        case _DP_SCALER_LANE2:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F);

            break;

        case _DP_SCALER_LANE3:

            ucAutoVCOBand = (ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F);

            break;
    }

    // [1:0] freqdet_lane_sel
    ScalerSetBit_EXINT(PB0_51_DP_SIG_DET_1, ~(_BIT1 | _BIT0), ucDpRx1LaneNumber);

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done -> 50us
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);

        if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

        if(g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] < g_pusDpRx1ClockCount[ucDpRx1LaneNumber])
        {
            ucBestVCOBand = ucAutoVCOBand + (((g_pusDpRx1ClockCount[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount1[ucDpRx1LaneNumber]) / usVCOBandDiff) + 1);
        }
        else
        {
            ucBestVCOBand = ucAutoVCOBand - ((g_pusDpRx1ClockCount1[ucDpRx1LaneNumber] - g_pusDpRx1ClockCount[ucDpRx1LaneNumber]) / usVCOBandDiff);
        }
    }
    else
    {
        ucBestVCOBand = ucAutoVCOBand;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    // Manually Reload FLD Band
    switch(ucDpRx1LaneNumber)
    {
        default:
        case _DP_SCALER_LANE0:

            ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE1:

            ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE2:

            ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;

        case _DP_SCALER_LANE3:

            ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ucBestVCOBand);

            break;
    }
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

    // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation with Independent LE Loop(Loop Mode 3)
    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetByte_EXINT(P7A_E0_MODE_TIMER, 0xF2);

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

    // Tap0 Max is 21
    ScalerSetByte_EXINT(P7A_E6_LIMIT_1, 0x35);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Tap1 Min is 49
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT0));
    }
    else
    {
        // Tap1 Min is 51
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1 | _BIT0));
    }

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

    // Tap0 Threshold = 10
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Set Vth Max = 6, Min = 4
        ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x64);
    }
    else
    {
        // Set Vth Max = 6, Min = 2
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

    // [1] tap1_trans = 1'b0 --> Tap1 is Effective every bit
    // [0] tap0_trans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit_EXINT(P7A_E3_GAIN_2, ~(_BIT1 | _BIT0), 0x00);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [1:0] trans_rlength = 2'b01 --> Tap0 Run Length = 3
        ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [1:0] trans_rlength = 2'b00 --> Tap0 Run Length = 2
        ScalerSetBit_EXINT(P7A_E4_GAIN_3, ~(_BIT1 | _BIT0), 0x00);
    }

    // [5] servo_notrans = 1'b0 --> Servo is Effective every bit
    // [4] tap0_notrans = 1'b0 --> Tap0 is Effective every bit
    ScalerSetBit_EXINT(P7A_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // LE Max = 18, Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x20);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0xD0);
    }
    else
    {
        // LE Max = 20, Initial = 16, Servo Initial = 16
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_D2_L3_LIMIT_INIT, 0x40);
        ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0xD0);
        ScalerSetByte_EXINT(P7A_D3_L3_INIT_1, 0xD0);
    }

    // Tap0 Initial Value = 18
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, 0x12);
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, 0x12);

    // Tap1 Initial Value = 15
    ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, 0x0F);
    ScalerSetByte_EXINT(P7A_D5_L3_INIT_3, 0x0F);

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

    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_DA_L3_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
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

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, 0x00);

#if(_MULTI_DISPLAY_MAX == 0x01)
    // [7:4] Rx_en = 4'b0000 -> Disable RX_EN
    // [3:0] CDR_en = 4'b0000 -> Disable CDR_EN
    ScalerSetByte_EXINT(P7A_1A_CMU_00, 0x00);

    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [7:6] reg_en_ana_cdr = 4'b0001 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7:6] reg_en_ana_cdr = 4'b0010 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), 0x00);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [7:6] reg_en_ana_cdr = 4'b0100 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT6);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7:6] reg_en_ana_cdr = 4'b1000 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), _BIT7);
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), 0x00);
            }

            // [4:3] DP Mac Select One Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE0_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE0)
            {
                // [4] Enable Lane0 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT4, _BIT4);

                // [0] Enable Lane0 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT0, _BIT0);

                // [6] reg_en_ana_cdr[0] = 1 --> Enable Lane0 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE1)
            {
                // [5] Enable Lane1 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT5, _BIT5);

                // [1] Enable Lane1 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT1, _BIT1);

                // [7] reg_en_ana_cdr[1] = 1 --> Enable Lane1 Analog CDR
                ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~_BIT7, _BIT7);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE2)
            {
                // [6] Enable Lane2 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT6, _BIT6);

                // [2] Enable Lane2 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT2, _BIT2);

                // [6] reg_en_ana_cdr[2] = 1 --> Enable Lane2 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT6, _BIT6);
            }
            else if(GET_DP_RX1_PCB_LANE1_MAPPING() == _DP_SCALER_LANE3)
            {
                // [7] Enable Lane3 Rx_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT7, _BIT7);

                // [3] Enable Lane3 CDR_en
                ScalerSetBit_EXINT(P7A_1A_CMU_00, ~_BIT3, _BIT3);

                // [7] reg_en_ana_cdr[3] = 1 --> Enable Lane3 Analog CDR
                ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~_BIT7, _BIT7);
            }

            // [4:3] DP Mac Select Two Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [7:4] Enable Lane0~3 Rx_en
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

            // [3:0] Enable Lane0~3 CDR_en
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P7A_1A_CMU_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

            // [7:6] reg_en_ana_cdr = 4'b1111 --> Enable Lane0~3 Analog CDR
            ScalerSetBit_EXINT(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
            ScalerSetBit_EXINT(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            // [4:3] DP Mac Select Four Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#else
    switch(g_ucDpRx1LaneCount)
    {
        case _DP_ONE_LANE:

            // [4:3] DP MAC Select One Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT3);

            break;

        case _DP_TWO_LANE:

            // [4:3] DP MAC Select Two Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), _BIT4);

            break;

        case _DP_FOUR_LANE:
        default:

            // [4:3] DP MAC Select Four Lane
            ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

            break;
    }
#endif


    ///////////////////////
    // Frequency Setting //
    ///////////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [7:5] rate_sel = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P7A_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

        // [2:0] SEL_DIV = 3'b000 --> 3~6GHz
        ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    }
    else
    {
        // [7:5] rate_sel = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P7A_44_ST_01, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

        // [2:0] SEL_DIV = 3'b001 --> 1.5~3GHz
        ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    }

    if(enumDpNFCodeRef == _DP_NF_REF_XTAL)
    {
        // [3] reg_xtal_en = 1'b1 --> Using 27M Xtal
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT3, _BIT3);

        if(g_ucDpRx1LinkRate == _DP_LINK_RBR)
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 300
            // 25/300 = 1/12 = 5*(27M/1.62G)
            ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0x2B);
        }
        else
        {
            // Analog CDR Auto FLD Counter
            // 0x2D[1] 0x2E --> ref_conuter = 25
            // 0x2D[0] 0x2F --> cdr_counter = 500
            // 25/500 = 1/20 = 5*(27M/2.7G)
            ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x18);
            ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0xF3);
        }
    }
    else
    {
        // [3] reg_xtal_en = 1'b0 --> Using D10.2 Clock
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT3, 0x00);

        // Analog CDR Auto FLD Counter
        // ref_conuter = 125
        // cdr_counter = 250
        // 250/500 = 1/2 = 5*(D10.2_clock / data_rate)
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_2E_ANA_CDR_03, 0x7C);
        ScalerSetByte_EXINT(P7A_2F_ANA_CDR_04, 0xF9);
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [4] Disable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, _BIT4);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 --> Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0xF0);


    //////////////////
    // ACDR Setting //
    //////////////////

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 1.5K
        // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
        ScalerSetByte_EXINT(P7A_31_ANA_CDR_06, 0x22);
    }
    else
    {
        // [7] reg_sel_CDR_cp = 0 --> Disable CDR Loop's CP (1nF)
        // [6:4] reg_sel_cdr_res = 3'b100 --> Analog CDR Rs = 4K
        // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
        ScalerSetByte_EXINT(P7A_31_ANA_CDR_06, 0x45);
    }


    /////////////////
    // DFE Setting //
    /////////////////

    // [7:3] Tap_EN = 5'b11111 --> Enable Tap0~4
    ScalerSetBit_EXINT(P7A_21_CMU_07, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();

    // [3:1] LE_lowgain_highboost = 3'b100 --> LE HighBoost Mode
    ScalerSetBit_EXINT(P7A_22_CMU_08, ~(_BIT3 | _BIT2 | _BIT1), _BIT3);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P7A_1D_CMU_03, ~_BIT4, 0x00);

    switch(g_ucDpRx1LinkRate)
    {
        case _DP_LINK_HBR2:

            // LE Peaking = 3GHz
            // [7:5] LE_RLSEL = 3'b000
            // [4:2] LE_ISEL = 3'b011
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            break;

        case _DP_LINK_HBR:

            // LE Peaking = 1.7GHz
            // [7:5] LE_RLSEL = 3'b001
            // [4:2] LE_ISEL = 3'b010
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

            break;

        case _DP_LINK_RBR:
        default:

            // LE Peaking = 900MHz
            // [7:5] LE_RLSEL = 3'b011
            // [4:2] LE_ISEL = 3'b000
            ScalerSetBit_EXINT(P7A_23_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));

            break;
    }


    //////////////
    // K Offset //
    //////////////

    // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

    // [6] en_fore_offset --> Toggle Foreground Calibration
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
    ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

    // Waiting for K Offset
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

    // Enable Vth/Tap0 Adaptation
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);

    // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

    // Waiting for FLD Lock Band
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

    // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, 0x00);

    // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT4, _BIT4);

    // Disable All Adapation Loop
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

    // Read Back Tap0 Max
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

    // Reload Max Value of Tap0 (Lane0)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane1)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane2)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Max Value of Tap0 (Lane3)
    ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetByte_EXINT(P7A_D4_L3_INIT_2, (ScalerGetByte_EXINT(P7A_F3_COEF_4) & 0x1F));

    // Reload Tap0
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, _BIT0);
    ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);
    ScalerSetBit_EXINT(P7A_DA_L3_INIT_8, ~_BIT0, 0x00);

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT3, _BIT3);

    // [6] DP Mac Clock Select to Link Clock
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT6, 0x00);


    /////////////////////////
    // D10.2 Clock Measure //
    /////////////////////////

    // [7:4] reg_en_sigdet_lane = 4'b1111 --> Enable Signal Detection for D10.2
    ScalerSetBit_EXINT(P7A_19_IMPEDANCE_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // [5] ln_ck_sel = 1'b0 -> DP Raw Data
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

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

        if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            break;
        }
    }

    if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
    {
        g_pusDpRx1ClockCount[0] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));
    }
    else
    {
        switch(g_ucDpRx1LinkRate)
        {
            case _DP_LINK_HBR2:

                g_pusDpRx1ClockCount[0] = 0x2710;

                break;

            case _DP_LINK_HBR:

                g_pusDpRx1ClockCount[0] = 0x1388;

                break;

            default:
            case _DP_LINK_RBR:

                g_pusDpRx1ClockCount[0] = 0xBB8;

                break;
        }
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    g_pusDpRx1ClockCount[3] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[2] = g_pusDpRx1ClockCount[0];
    g_pusDpRx1ClockCount[1] = g_pusDpRx1ClockCount[0];
}

//--------------------------------------------------
// Description  : DP Phy Setting in TP2
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1Tp2SetPhy_EXINT0(void) using 1
{
    WORD usVCOBandDiff = 0;
    WORD usVCOBandScan = 0;
    BYTE ucIcp = (ScalerGetByte_EXINT(P7A_31_ANA_CDR_06) & 0x0F);


    /////////////
    // Rx Misc //
    /////////////

    // Digital PHY Block Power Normal
    ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b0 --> Disable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, 0x00);

    // [4] Enable Comma Detection
    ScalerSetBit_EXINT(PB0_05_SAMPLE_EDGE, ~_BIT4, 0x00);

    // [5] Disable De-Scrambling
    ScalerSetBit_EXINT(PB0_07_SCRAMBLE_CTRL, ~_BIT5, _BIT5);

    if((ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x01, 0x01) & _BIT7) == _BIT7)
    {
        // [2] Enable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, _BIT2);
    }
    else
    {
        // [2] Disable Enhancement Control Mode
        ScalerSetBit_EXINT(PB0_01_PHY_DIG_RESET_CTRL, ~_BIT2, 0x00);
    }

    // [4] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
    // [3] reg_en_data_manual_l0 = 1'b0
    // [2] reg_bypass_data_rdy_l0 = 1'b1
    // [1] reg_en_eqen_manual_l0 = 1'b0
    // [0] reg_bypass_eqen_rdy_l0 = 1'b1
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2 | _BIT0));

    // [7:4] RST_N = 4'b0000 = 4'b1111 -->Digital Circuit Reset Toggle
    // [3:0] CDR_RST_N = 4'b0000 --> Disable DCDR
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0x00);
    ScalerSetByte_EXINT(P7A_3A_TMDS_RESET, 0xF0);

    // [4] en_sumamp_highgain = 0 --> Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(P7A_1D_CMU_03, ~_BIT4, 0x00);

    // Set DFE Initial
    ScalerDpRx1SetDFEInitial_EXINT0();


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(P7A_1B_CMU_01, ~_BIT7, _BIT7);

    // [7] reg_auto_mode = 1'b1 --> FLD Auto Mode
    // [4] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
    // [0] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT4 | _BIT0), (_BIT7 | _BIT0));

    // [2] reg_rstb_fsm --> FLD Reset
    ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, 0x00);

    // [1] reg_en_eqen_manual_l0 = 1'b1 --> DFE Adaptation Enable
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, _BIT1);

    if(g_ucDpRx1LinkRate == _DP_LINK_HBR2)
    {
        // Enable Vth/LE/Tap0~4
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xDF);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xDF);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Waiting for FLD Lock Band
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 20; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [1] reg_en_eqen_manual_l0 = 1'b0 --> DFE Adaptation Off
        ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT1, 0x00);

        // Disable LE/Vth/Tap0~4
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);

        // [4] reg_adp_eq_off = 1'b1 --> Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT4, _BIT4);


        //////////////
        // K Offset //
        //////////////

        // [5] fore_off_autok = 1 --> Enable Foreground Calibration Auto Mode
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT5, _BIT5);

        // [6] en_fore_offset --> Toggle Foreground Calibration
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7A_24_KOFFSET_00, ~_BIT6, _BIT6);

        // Waiting for DFE Adaptation
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }
    }
    else
    {
        // Enable LE/Vth/Tap0~2 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0xC7);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0xC7);

        // [2] reg_rstb_fsm = 1'b1 --> Lock FLD Band, CDR Close Loop, DFE Adaptation Enable
        ScalerSetBit_EXINT(P7A_2D_ANA_CDR_02, ~_BIT2, _BIT2);

        // Waiting for FLD Lock Band
        for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 40; g_ucDpRx1Temp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Disable Adapation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x00);
    }


    /////////////////////
    // FLD Manual Mode //
    /////////////////////

    // [6] reg_adp_en_manual = 1'b0 --> CDR Open Loop
    // [5] reg_cp_en_manual = 1'b0 --> CDR Open Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT6 | _BIT5), 0x00);

    // Scan Auto FLD + 4
    ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F) + 4));
    ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F) + 4));

    // [7] reg_auto_mode = 1'b0 --> FLD Manual Mode
    // [6] reg_adp_en_manual = 1'b1 --> Enable VCO Clock Out
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~(_BIT7 | _BIT6), _BIT6);

    // Waiting for VCO Stable
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }


    /////////////////////////
    // Scan Auto Band + 4  //
    /////////////////////////

    // [5] ln_ck_sel = 1'b1 -> CDR Clock
    // [4:0] DP_XTAL_CYCLE = 5'b00011 -> XTAL Counter Cycles = 1000
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT1 | _BIT0));

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

        if(ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6)
        {
            usVCOBandScan = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

            // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
            ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

            break;
        }
    }


    /////////////////////////
    // VCO Band Difference //
    /////////////////////////

    // Scan Auto FLD
    ScalerSetBit_EXINT(P7A_32_ANA_CDR_07, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_36_ANA_CDR_11) & 0x7F));
    ScalerSetBit_EXINT(P7A_33_ANA_CDR_08, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_37_ANA_CDR_12) & 0x7F));
    ScalerSetBit_EXINT(P7A_34_ANA_CDR_09, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_38_ANA_CDR_13) & 0x7F));
    ScalerSetBit_EXINT(P7A_35_ANA_CDR_10, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ScalerGetByte_EXINT(P7A_39_ANA_CDR_14) & 0x7F));

    // Waiting for VCO Stable
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [6] LANE_COUNT_CLEAR = 0 -> Keep the LANE_COUNT value
    ScalerSetBit_EXINT(PB0_52_DP_SIG_DET_2, ~_BIT6, 0x00);

    // [7] DP_SIG_DET_EN = 1'b1 -> Enable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, _BIT7);

    // Waiting for Measure Done -> 50us
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 10; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);

        // FLD + 4 Measure Fail or Measure Done
        if((usVCOBandScan == 0) || (ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6))
        {
            break;
        }
    }

    // Measure Done
    if((usVCOBandScan != 0) && (ScalerGetBit_EXINT(PB0_50_DP_SIG_DET_0, _BIT6) == _BIT6))
    {
        g_pusDpRx1ClockCount1[_D1_DP_LANE0] = ((((WORD)ScalerGetByte_EXINT(PB0_53_DP_SIG_DET_3)) << 8) | ScalerGetByte_EXINT(PB0_54_DP_SIG_DET_4));

        usVCOBandDiff = (abs(usVCOBandScan - g_pusDpRx1ClockCount1[_D1_DP_LANE0]) >> 2);
    }
    else
    {
        usVCOBandDiff = 0;
    }

    // [7] DP_SIG_DET_EN = 0 -> Disable Signal Detection
    ScalerSetBit_EXINT(PB0_50_DP_SIG_DET_0, ~_BIT7, 0x00);

    if(usVCOBandDiff != 0)
    {
        switch(g_ucDpRx1LaneCount)
        {
            case _DP_FOUR_LANE:

                // Lane3 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE3, usVCOBandDiff);

                // Lane2 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE2, usVCOBandDiff);

                // Lane1 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;

            case _DP_TWO_LANE:

                // Lane1 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE1, usVCOBandDiff);

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;

            default:
            case _DP_ONE_LANE:

                // Lane0 VCO Adjust
                ScalerDpRx1AdjustLaneFLDBand_EXINT0(_D1_DP_LANE0, usVCOBandDiff);

                break;
        }
    }

    // [3:0] reg_cdr_cp_in --> Double Icp to Enlarge Locking Range
    if(ucIcp > 7)
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (ucIcp << 1));
    }

    // Waiting for VCO Stable
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 2; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [5] reg_cp_en_manual = 1'b1 --> CDR Close Loop
    ScalerSetBit_EXINT(P7A_2C_ANA_CDR_01, ~_BIT5, _BIT5);

    // Waiting for CDR Close Loop
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [3:0] reg_cdr_cp_in --> Restore Icp to Original Setting
    ScalerSetBit_EXINT(P7A_31_ANA_CDR_06, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucIcp);

    // Waiting for CDR Close Loop
    for(g_ucDpRx1Temp = 0; g_ucDpRx1Temp <= 5; g_ucDpRx1Temp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    if(g_ucDpRx1LinkRate <= _DP_LINK_HBR)
    {
        // Set Vth Min = 0
        ScalerSetBit_EXINT(P7A_F9_LIMIT_10, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

        // Only Enable Vth/Tap0 Adapation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_D1_L3_DFE_EN_2, 0x41);
    }

    // [3] reg_en_data_manual_l0 = 1'b1 --> Data from PHY to MAC
    ScalerSetBit_EXINT(P7A_12_ANA_CDR, ~_BIT3, _BIT3);
}

//--------------------------------------------------
// Description  : DP Interrupt Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpRx1IntHandler_EXINT0(void) using 1
{
#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    BYTE ucDPCDAddress = 0;
#endif

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
            ScalerSetBit_EXINT(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);

            // Disable Aux Power Saving Mode
            ScalerSetBit_EXINT(PBA_62_AUX_2, ~_BIT1, 0x00);

            // Switch Aux PHY to GDI BandGap
            ScalerSetBit_EXINT(PBA_63_AUX_3, ~_BIT7, 0x00);

            // Aux comm current select max
            ScalerSetBit_EXINT(PBA_64_AUX_4, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            SET_DP_RX1_PS_AUX_TOGGLE();

            IP = 0xA0;

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
            // DPCD 022xxh Into INT
            if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) != (_BIT7 | _BIT6))
#endif
            {
                return;
            }
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

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
    if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
    {
        // Aux Firmware Control -> Reply Defer
        ScalerSetBit_EXINT(PBA_D0_AUX_MODE_SET, ~_BIT1, 0x00);
    }
    else
#endif
    {
        if(ScalerGetBit_EXINT(PBA_D0_AUX_MODE_SET, _BIT1) == _BIT1)
        {
            // Aux Firmware Control -> Reply Defer
            SET_DP_RX1_AUX_MANUAL_MODE_EXINT();
        }
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

#if(_DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORT == _ON)
        // DPCD 022xxh Into INT
        if(ScalerGetBit_EXINT(PBA_FB_DUMMY_1, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6))
        {
            // Clear Flag
            ScalerSetBit_EXINT(PBA_FB_DUMMY_1, ~(_BIT7 | _BIT5 | _BIT3 | _BIT1), _BIT7);

            ucDPCDAddress = (ScalerGetByte_EXINT(PBA_D4_AUX_RX_ADDR_L));

            // Reset Aux FIFO
            ScalerSetBit_EXINT(PBA_DA_AUX_FIFO_RST, ~_BIT0, _BIT0);

            pData_EXINT[1] = (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F) + 1;
            ucDPCDAddress -= pData_EXINT[1];

            if(ucDPCDAddress <= 0x0F)
            {
                if(ucDPCDAddress == 0x00)
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, _DP_VERSION_1_4);
                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                if((pData_EXINT[1] > 0) && (ucDPCDAddress == 0x01))
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, _D1_DP_LINK_CLK_RATE);
                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                if((ucDPCDAddress + pData_EXINT[1]) > 16)
                {
                    // pData_EXINT[2] is The Address of DPCD Table
                    for(pData_EXINT[2] = ucDPCDAddress; pData_EXINT[2] <= 0x0F; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, pData_EXINT[2]));
                    }

                    // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x08);

                    for(pData_EXINT[2] = pData_EXINT[2]; pData_EXINT[2] <= pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x00);
                    }
                }
                else
                {
                    for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                    {
                        ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, ScalerDpRx1GetDpcdInfo_EXINT0(0x00, 0x00, (ucDPCDAddress + pData_EXINT[2])));
                    }
                }
            }
            else
            {
                // Set DPCD 02210h[3] = 1 --> VSC_SDP_EXTENSION_FOR_COLORIMETRY_SUPPORTED
                if(ucDPCDAddress == 0x10)
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x08);
                    ucDPCDAddress++;
                    pData_EXINT[1]--;
                }

                for(pData_EXINT[2] = 0; pData_EXINT[2] < pData_EXINT[1]; pData_EXINT[2]++)
                {
                    ScalerSetByte_EXINT(PBA_D9_AUX_TX_DATA, 0x00);
                }
            }

            // Reload The Length of Aux Message
            ScalerSetByte_EXINT(PBA_D8_AUX_TX_LEN, (ScalerGetByte_EXINT(PBA_D5_AUX_RXLEN) & 0x0F));
        }
#endif
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

#if(_DP_HDCP_2_2_SUPPORT == _ON)
            // Switch HDCP to 1.4 Module from 2.2 Module as receiving AKsv
            if((ScalerGetBit_EXINT(PB0_1A_HDCP_IRQ, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(PB0_20_HDCP_DEBUG, _BIT7) == _BIT7))
            {
                // Select to HDCP 1.4 Module
                ScalerSetBit_EXINT(PB0_1A_HDCP_IRQ, _BIT1, 0x00);

                // Calculate R0' by manual toggle HDCP 1.4 Module
                ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, _BIT7);
                ScalerSetBit_EXINT(PB0_63_HDCP_OTHER, ~_BIT7, 0x00);
            }
#endif

#if((_DP_TX_SUPPORT == _ON) && (_D1_DP_MST_PORT_SUPPORT == _ON))
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
        // Detect if Aksv(0x6800B) is Written by Source
        if(ScalerGetBit_EXINT(PBA_A5_AUX_RESERVE5, (_BIT6 | _BIT2)) == (_BIT6 | _BIT2))
        {
            ScalerSetBit_EXINT(PBA_A5_AUX_RESERVE5, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

            ScalerDpRx1HDCPResetDpcdInfo_EXINT0();

            SET_DP_RX1_HDCP_AUTH_AKSV_WRITTEN();
        }

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

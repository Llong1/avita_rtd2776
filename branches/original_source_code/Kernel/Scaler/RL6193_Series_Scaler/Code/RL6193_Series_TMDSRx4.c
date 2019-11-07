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
// ID Code      : RL6193_Series_TMDSRx4.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

#if(_D4_TMDS_SUPPORT == _ON)

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
#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
BYTE g_pucTmdsRx4Caps[3];
#endif

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx4InterruptInitial(void);
void ScalerTMDSRx4SetDFEInitial_EXINT0(void);
void ScalerTMDSRx4SetPhy_EXINT0(void);
void ScalerTMDSRx4IntHandler_EXINT0(void);
WORD ScalerTMDSRx4MeasureClk(BYTE ucMeasureClk);
WORD ScalerTMDSRx4MeasureClk_EXINT0(BYTE ucMeasureClk);

#if(_D4_HDMI_SUPPORT == _ON)
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
bit ScalerTMDSRx4HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
#endif
#endif


#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
BYTE ScalerTMDSRx4TMDSScanInputPort(BYTE ucInputType);
#endif
#endif

bit ScalerTMDSRx4TMDSStableDetect(BYTE ucSourceType);
void ScalerTMDSRx4HotPlugEvent(void);

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
bit ScalerTMDSRx4GetDualDVIMode(void);
BYTE ScalerTMDSRx4GetDualDVIMode_EXINT0(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4InterruptInitial(void)
{
    if(ScalerGetBit(P73_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_RX4_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(PB3_A1_CMU_01, ~_BIT7, _BIT7);

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Set Freq. Reference Counter = 1000
    ScalerSetBit(P73_F6_HDMI_FREQDET_BOUND_H, ~(_BIT1 | _BIT0), 0x00);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P73_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Upper Bound
        ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
    }
    else
#endif
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P73_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
        // Set Upper Bound
        ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
        ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
        ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
    }

    // Set Lower Bound
    ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
    ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

    // Set Stable Time (0x7F = about 5ms)
    ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x7F);

    // Disable Freq. Unstable IRQ
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

    // Enable Freq. Stable IRQ
    ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_60_PORT_PAGE73_HDMI_INTCR, ~_BIT7, _BIT7);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

    EX0 = 1;

    // Start Freq. Detection
    ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : TMDS DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4SetDFEInitial_EXINT0(void) using 1
{
    // [7] Positive Symbol-Rate Clock
    // [6] Enable Timer Control DFE Loop
    // [5:4] No Reduce Gain
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P7D_A0_L0_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P7D_B0_L1_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));
    ScalerSetBit_EXINT(P7D_C0_L2_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6));

    if(GET_D4_INPUT_PIXEL_CLK() > 1000)
    {
        // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation without Independent LE Loop
        ScalerSetBit_EXINT(P7D_E0_MODE_TIMER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop
        ScalerSetBit_EXINT(P7D_E0_MODE_TIMER, ~(_BIT7 | _BIT6), _BIT7);
    }

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit_EXINT(P7D_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Set DFE Delay Time
    // Turn On LE/Tap1~6 Simultaneously
    ScalerSetByte_EXINT(P7D_E1_TIMER, 0x01);

    // Filter's Gain of Tap0~4/Servo/LE
    // Tap0_Gain = 1/512, Tap1_Gain = 1/512
    // Tap2_Gain = 1/512; Tap3_Gain = 1/512
    // Tap4_Gain = 1/512; Servo_Gain = 1/256
    // LE_Gain1 = 1/256, LE_Gain2 = 1/512
    ScalerSetBit_EXINT(P7D_E2_GAIN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit_EXINT(P7D_E3_GAIN_2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit_EXINT(P7D_E4_GAIN_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));
    ScalerSetBit_EXINT(P7D_E5_GAIN_4, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));

    // Tap0 = 0~21
    // Vth_Threshold = 1
    // Tap0_Threshold = 10
    ScalerSetByte_EXINT(P7D_E6_LIMIT_1, 0x35);
    ScalerSetBit_EXINT(P7D_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // LE = 0~24
    if(GET_D4_INPUT_PIXEL_CLK() > 1000)
    {
        // Tap1 = 0~55 in Mode3
        ScalerSetByte_EXINT(P7D_E7_LIMIT_2, 0x37);
    }
    else
    {
        // Tap1 = 0~31 in Mode2
        ScalerSetByte_EXINT(P7D_E7_LIMIT_2, 0x1F);
    }

    // Tap2 = -25~10
    // Tap3~4 = -25~6
    ScalerSetByte_EXINT(P7D_E8_LIMIT_3, 0x56);
    ScalerSetByte_EXINT(P7D_E9_LIMIT_4, 0x46);
    ScalerSetByte_EXINT(P7D_EA_LIMIT_5, 0xC9);
    ScalerSetByte_EXINT(P7D_EB_LIMIT_6, 0x99);

    // Vth_max = 6
    // Vth_min = 0
    ScalerSetByte_EXINT(P7D_F9_LIMIT_10, 0x60);

    // Set Vth/Tap Divider
    // Servo_Divider = 40
    // Vth_Divider = 15
    // Tap_Divider = 10
    ScalerSetByte_EXINT(P7D_EC_LOOP_DIV_1, 0xA3);
    ScalerSetByte_EXINT(P7D_ED_LOOP_DIV_2, 0xCA);

    // [5] servo_notrans = 1'b0 --> Each Bit is Effective in Servo
    // [4] tap0_notrans = 1'b0 --> Each Bit is Effective in Tap0
    ScalerSetBit_EXINT(P7D_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), _BIT4);

    // [1] De_inverse = 1'b0 --> Adapation Only for Blanking Area (Transition Maximum)
    // [0] De_brank_en = 1'b0 --> Disable Blank Function of gdi_de
    ScalerSetBit_EXINT(P7D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), 0x00);

    // Initial DFE Code
    if(GET_D4_INPUT_PIXEL_CLK() < 375)
    {
        ScalerSetByte_EXINT(P7D_A2_L0_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P7D_B2_L1_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P7D_C2_L2_LIMIT_INIT, 0x84);
    }
    else if(GET_D4_INPUT_PIXEL_CLK() < 1000)
    {
        ScalerSetByte_EXINT(P7D_A2_L0_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P7D_B2_L1_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P7D_C2_L2_LIMIT_INIT, 0x86);
    }
    else
    {
        ScalerSetByte_EXINT(P7D_A2_L0_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P7D_B2_L1_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P7D_C2_L2_LIMIT_INIT, 0x8C);
    }

    ScalerSetByte_EXINT(P7D_A3_L0_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7D_B3_L1_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7D_C3_L2_INIT_1, 0x90);

    ScalerSetByte_EXINT(P7D_A4_L0_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P7D_B4_L1_INIT_2, 0x0F);
    ScalerSetByte_EXINT(P7D_C4_L2_INIT_2, 0x0F);

    if(GET_D4_INPUT_PIXEL_CLK() > 1000)
    {
        ScalerSetByte_EXINT(P7D_A5_L0_INIT_3, 0x0C);
        ScalerSetByte_EXINT(P7D_B5_L1_INIT_3, 0x0C);
        ScalerSetByte_EXINT(P7D_C5_L2_INIT_3, 0x0C);
    }
    else
    {
        ScalerSetByte_EXINT(P7D_A5_L0_INIT_3, 0x00);
        ScalerSetByte_EXINT(P7D_B5_L1_INIT_3, 0x00);
        ScalerSetByte_EXINT(P7D_C5_L2_INIT_3, 0x00);
    }

    ScalerSetByte_EXINT(P7D_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7D_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7D_C6_L2_INIT_4, 0x00);

    ScalerSetByte_EXINT(P7D_A7_L0_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7D_B7_L1_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7D_C7_L2_INIT_5, 0x00);

    ScalerSetByte_EXINT(P7D_A8_L0_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7D_B8_L1_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7D_C8_L2_INIT_6, 0x00);

    ScalerSetByte_EXINT(P7D_A9_L0_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7D_B9_L1_INIT_7, 0x04);
    ScalerSetByte_EXINT(P7D_C9_L2_INIT_7, 0x04);

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7D_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7D_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7D_CA_L2_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7D_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7D_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7D_CA_L2_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7D_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : TMDS Set PHY Function (EXINT0 Only)
// Input Value  : Measured Clk Count for PHY Setting
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4SetPhy_EXINT0(void) using 1
{
    BYTE ucTemp = 0;

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
    BYTE pucLEMax[3];
    BYTE pucTap0Max[3];
    BYTE pucVth[3];
#endif

    ///////////////
    // RX CMU EN //
    ///////////////

    // [7] cmu_en = 0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB3_A7_CMU_07, ~_BIT7, 0x00);

    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6)  // MHL Mode
    {
        // [7:4] rx_en = 4'b1001 --> Enable RXEN for Lane0, 3
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

        // [5] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB3_A7_CMU_07, ~_BIT5, _BIT5);

        // [3:0] cdr_en = 4'b0001 --> Enable CDREX for Lane0
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [7:4] rx_en = 4'b1111 --> Enable RXEN
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [5] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB3_A7_CMU_07, ~_BIT5, _BIT5);

        // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(PB3_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }


    /////////////////
    // CMU Setting //
    /////////////////

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6)   // MHL Mode
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            if(GET_D4_INPUT_PIXEL_CLK() <= 3000)
            {
                // [7:5] rate_sel = 3'b001 --> 2250MHz ~ 3000MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [7:5] SEL_DIV = 3'b001 --> 2250MHz ~ 3000MHz
                ScalerSetBit_EXINT(PB3_A3_CMU_03, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [0] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB3_AB_CDR_02, ~_BIT0, _BIT0);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB3_F9_LANE0_A_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB3_FA_LANE0_A_CDR_04, 0xEF);
                ScalerSetByte_EXINT(PB3_FB_LANE0_A_CDR_05, 0x1D);
                ScalerSetByte_EXINT(PB3_FC_LANE0_A_CDR_06, 0xC5);

                // [4:2] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 2K
                ScalerSetBit_EXINT(PB3_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), _BIT3);

                // [3:0] reg_cdr_cp_in = 4'b0011 --> Analog CDR Icp = 10.5uA
                ScalerSetBit_EXINT(PB3_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
            else
            {
                // [7:5] rate_sel = 3'b000 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [7:5] SEL_DIV = 3'b000 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(PB3_A3_CMU_03, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [0] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB3_AB_CDR_02, ~_BIT0, _BIT0);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB3_F9_LANE0_A_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB3_FA_LANE0_A_CDR_04, 0xEF);
                ScalerSetByte_EXINT(PB3_FB_LANE0_A_CDR_05, 0x3B);
                ScalerSetByte_EXINT(PB3_FC_LANE0_A_CDR_06, 0xC5);

                // [4:2] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 2K
                ScalerSetBit_EXINT(PB3_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), _BIT3);

                // [3:0] reg_cdr_cp_in = 4'b0011 --> Analog CDR Icp = 10.5uA
                ScalerSetBit_EXINT(PB3_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
        }
        else  // MHL 24bit Mode
        {
            // [7:4] CMU_SEL_PUMP_I = 4'b0100 --> Icp = 12.5uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
            ScalerSetByte_EXINT(PB3_A4_CMU_04, 0x47);

            if((GET_D4_INPUT_PIXEL_CLK() >= 700) && (GET_D4_INPUT_PIXEL_CLK() < 1125))
            {
                // [7:5] rate_sel = 3'b010 --> 750MHz ~ 1125MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

                // [7:5] SEL_DIV = 3'b010 --> 750MHz ~ 1125MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x50);

                // [7:0] N_CODE = 8'b0011 1000 --> 56 + 4 = 60
                ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x38);
            }
            else if((GET_D4_INPUT_PIXEL_CLK() >= 1125) && (GET_D4_INPUT_PIXEL_CLK() < 1500))
            {
                // [7:5] rate_sel = 3'b010 --> 1125MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

                // [7:5] SEL_DIV = 3'b010 --> 1125MHz ~ 1500MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x51);

                // [7:0] N_CODE = 8'b0111 0100 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x74);
            }
            else if((GET_D4_INPUT_PIXEL_CLK() >= 1500) && (GET_D4_INPUT_PIXEL_CLK() < 2000))
            {
                // [7:5] rate_sel = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [7:5] SEL_DIV = 3'b001 --> 1500MHz ~ 2250MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b10 --> /4
                ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x32);

                // [7:0] N_CODE = 8'b0111 0100 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x74);
            }
            else if(GET_D4_INPUT_PIXEL_CLK() <= 3000)
            {
                // [7:5] rate_sel = 3'b001 --> 2250MHz ~ 3000MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [7:5] SEL_DIV = 3'b001 --> 2250MHz ~ 3000MHz
                ScalerSetBit_EXINT(PB3_A3_CMU_03, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [0] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB3_AB_CDR_02, ~_BIT0, _BIT0);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB3_F9_LANE0_A_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB3_FA_LANE0_A_CDR_04, 0xEF);
                ScalerSetByte_EXINT(PB3_FB_LANE0_A_CDR_05, 0x27);
                ScalerSetByte_EXINT(PB3_FC_LANE0_A_CDR_06, 0xC5);

                // [4:2] reg_sel_cdr_res = 3'b101 --> Analog CDR Rs = 6K
                ScalerSetBit_EXINT(PB3_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), (_BIT4 | _BIT2));

                // [3:0] reg_cdr_cp_in = 4'b0101 --> Analog CDR Icp = 16.5uA
                ScalerSetBit_EXINT(PB3_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            }
            else
            {
                // [7:5] rate_sel = 3'b001 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [7:5] SEL_DIV = 3'b001 --> 3000MHz ~ 6000MHz
                ScalerSetBit_EXINT(PB3_A3_CMU_03, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [0] en_wide_temp = 1'b1
                ScalerSetBit_EXINT(PB3_AB_CDR_02, ~_BIT0, _BIT0);

                // [6] xtal_en = 0 --> FLD Reference Input Clock
                // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
                // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
                ScalerSetBit_EXINT(PB3_F9_LANE0_A_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

                // Analog CDR Auto FLD Counter
                ScalerSetByte_EXINT(PB3_FA_LANE0_A_CDR_04, 0xEF);
                ScalerSetByte_EXINT(PB3_FB_LANE0_A_CDR_05, 0x4F);
                ScalerSetByte_EXINT(PB3_FC_LANE0_A_CDR_06, 0xC5);

                // [4:2] reg_sel_cdr_res = 3'b010 --> Analog CDR Rs = 2K
                ScalerSetBit_EXINT(PB3_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), _BIT3);

                // [3:0] reg_cdr_cp_in = 4'b0011 --> Analog CDR Icp = 10.5uA
                ScalerSetBit_EXINT(PB3_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            }
        }
    }
    else     // HDMI Mode
#endif
    {
        // [7:4] CMU_SEL_PUMP_I = 4'b1010 --> Icp = 27.5uA
        // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
        // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
        ScalerSetByte_EXINT(PB3_A4_CMU_04, 0xA6);

        if((GET_D4_INPUT_PIXEL_CLK() >= 187) && (GET_D4_INPUT_PIXEL_CLK() < 375))
        {
            // [7:5] rate_sel = 3'b100 --> 187.5MHz ~ 375MHz
            ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

            // [7:5] SEL_DIV = 3'b100 --> 187.5MHz ~ 375MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x90);

            // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
            ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x4C);
        }
        else if((GET_D4_INPUT_PIXEL_CLK() >= 375) && (GET_D4_INPUT_PIXEL_CLK() < 750))
        {
            // [7:5] rate_sel = 3'b011 --> 375MHz ~ 750MHz
            ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

            // [7:5] SEL_DIV = 3'b011 --> 375MHz ~ 750MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b01 --> /2
            ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x71);

            // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
            ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x4C);
        }
        else if((GET_D4_INPUT_PIXEL_CLK() >= 750) && (GET_D4_INPUT_PIXEL_CLK() < 1500))
        {
            // [7:5] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
            ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // [7:5] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b01 --> /2
            ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x51);

            // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x24);
        }
        else if((GET_D4_INPUT_PIXEL_CLK() >= 1500) && (GET_D4_INPUT_PIXEL_CLK() < 3000))
        {
            // [7:5] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
            ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // [7:5] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b10 --> /4
            ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x32);

            // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x24);
        }
        else if(GET_D4_INPUT_PIXEL_CLK() >= 3000)
        {
            // [7:5] rate_sel = 3'b000 --> 3000MHz ~ 3400MHz
            ScalerSetBit_EXINT(PB3_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] SEL_DIV = 3'b000 --> 3000MHz ~ 3400MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b11 --> Determined by CMU_PREDIVN
            ScalerSetByte_EXINT(PB3_A3_CMU_03, 0x13);

            // [4:1] CMU_PREDIVN = 4'b0110 --> /8 (N+2 Divider)
            ScalerSetBit_EXINT(PB3_A8_CMU_08, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

            // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB3_F2_SDM_01, 0x24);
        }
    }

    // [5] CMU_BYPASS_PI = 1'b1 --> Integer N PLL
    // [4] cmu_en_awdog = 1'b0 --> Disable CMU WaychDog
    // [3] CMU_CKSEL = 1'b1 --> Ref. TMDS Clock
    // [2] cmu_sel = 1'b0 --> CMU Feedback Loop Divider = 1
    ScalerSetBit_EXINT(PB3_A5_CMU_05, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // [7] BYPASS_PI = 1'b1 --> Use Integer N_CODE
    // [5] N_CODE[8] = 1'b0 --> N = N_CODE + 4
    ScalerSetBit_EXINT(PB3_F1_SDM_00, ~(_BIT7 | _BIT5), _BIT7);

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit_EXINT(PB3_F4_WD_00, ~_BIT0, 0x00);


    /////////////////
    // CDR Setting //
    /////////////////

    if((GET_D4_INPUT_PIXEL_CLK() >= 2500) && (GET_D4_INPUT_PIXEL_CLK() < 3000))
    {
        // [3:0] KD = 3'b111 --> KD = 1
        ScalerSetBit_EXINT(PB3_CC_ERROR_COUNT_0, ~(_BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2 | _BIT1));
    }
    else
    {
        // [3:0] KD = 3'b000 --> KD = 0
        ScalerSetBit_EXINT(PB3_CC_ERROR_COUNT_0, ~(_BIT3 | _BIT2 | _BIT1), 0x00);
    }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6) // MHL Mode
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            // KI = 3'b011 --> KI = 1/8
            ScalerSetBit_EXINT(PB3_D4_KI_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // KP = 0x33 --> KP = 12.75
            ScalerSetByte_EXINT(PB3_D6_KP_0, 0x33);
        }
        else
        {
            // KI = 3'b000 --> KI = 0
            ScalerSetBit_EXINT(PB3_D4_KI_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // KP = 0x2F --> KP = 11.75
            ScalerSetByte_EXINT(PB3_D6_KP_0, 0x2F);
        }
    }
    else   // HDMI Mode
#endif
    {
        // KI = 3'b000 --> KI = 0
        ScalerSetByte_EXINT(PB3_D4_KI_0, 0x00);
        ScalerSetByte_EXINT(PB3_D5_KI_1, 0x00);

        if(GET_D4_INPUT_PIXEL_CLK() < 2500)
        {
            // KP = 0x0F --> KP = 3.75
            ScalerSetByte_EXINT(PB3_D6_KP_0, 0x0F);
            ScalerSetByte_EXINT(PB3_D7_KP_1, 0x0F);
            ScalerSetByte_EXINT(PB3_D8_KP_2, 0x0F);
        }
        else if((GET_D4_INPUT_PIXEL_CLK() >= 2500) && (GET_D4_INPUT_PIXEL_CLK() < 3000))
        {
            // KP = 0x2D --> KP = 11.25
            ScalerSetByte_EXINT(PB3_D6_KP_0, 0x2D);
            ScalerSetByte_EXINT(PB3_D7_KP_1, 0x2D);
            ScalerSetByte_EXINT(PB3_D8_KP_2, 0x2D);
        }
        else
        {
            // KP = 0x17 --> KP = 5.75
            ScalerSetByte_EXINT(PB3_D6_KP_0, 0x17);
            ScalerSetByte_EXINT(PB3_D7_KP_1, 0x17);
            ScalerSetByte_EXINT(PB3_D8_KP_2, 0x17);
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

    // [0] en_clkout_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB3_F5_WD_01, ~_BIT4, 0x00);

    // [0] en_eqen_manual = 0 --> Disable Clkout
    ScalerSetBit_EXINT(PB3_F6_EQEN_TIMER, ~_BIT0, 0x00);

    // [0] en_data_manual = 0 --> Disable Dataout
    ScalerSetBit_EXINT(PB3_F7_DATA_TIMER, ~_BIT0, 0x00);

    // [3:0] RST_N = 4'b0000 --> Digital Circuit Reset
    ScalerSetBit_EXINT(PB3_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // [3:0] RST_N = 4'b1111 --> Digital Circuit Normal
    ScalerSetBit_EXINT(PB3_DA_PI_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6) &&
       (((GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)) ||
        ((GET_TMDS_RX4_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) && (GET_D4_INPUT_PIXEL_CLK() >= 2000))))
    {
        // [7] Enable Lane0 ACDR
        ScalerSetBit_EXINT(PB3_B9_LANE0_A_CDR_00, ~_BIT7, _BIT7);

        // [0] Enable Lane0 ACDR_DFE
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~_BIT0, _BIT0);

        // [4] reg_en_data_manual_l0 = 1'b0
        // [3] reg_bypass_data_rdy_l0 = 1'b1
        // [2] reg_en_eqen_manual_l0 = 1'b0
        // [1] reg_bypass_eqen_rdy_l0 = 1'b1
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));
    }
    else
#endif
    {
        // [7] Disable Lane0 ACDR
        ScalerSetBit_EXINT(PB3_B9_LANE0_A_CDR_00, ~_BIT7, 0x00);

        // [0] Disable Lane0 ACDR
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~_BIT0, 0x00);
    }


    /////////////////
    // DFE Setting //
    /////////////////

    // Load DFE Initial Code
    ScalerTMDSRx4SetDFEInitial_EXINT0();

    // [7:5] LE_lowgain_highboost = 1 --> LE HighBoost Mode
    ScalerSetBit_EXINT(PB3_A8_CMU_08, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    if(GET_D4_INPUT_PIXEL_CLK() < 2000)
    {
        // LE Peaking = 900Mpbs
        // [7:5] LE_ISEL = 3'b000
        // [4:2] LE_RLSEL = 3'b011
        ScalerSetBit_EXINT(PB3_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

        // [4] SEL_DFE_DELAY = 1'b1 --> Increase DFE Delay
        ScalerSetBit_EXINT(PB3_A6_CMU_06, ~_BIT4, _BIT4);
    }
    else
    {
        // LE Peaking = 1.7Gpbs
        // [7:5] LE_ISEL = 3'b010
        // [4:2] LE_RLSEL = 3'b001
        ScalerSetBit_EXINT(PB3_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));

        // [4] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
        ScalerSetBit_EXINT(PB3_A6_CMU_06, ~_BIT4, 0x00);
    }


    //////////////
    // K Offset //
    //////////////

    // [2] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB3_AD_CDR_04, ~_BIT2, _BIT2);

    // [5] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB3_AA_CDR_01, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB3_AA_CDR_01, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB3_AA_CDR_01, ~_BIT5, _BIT5);

    // Waiting for K Offset
    for(ucTemp = 0; ucTemp <= 6; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // Enable Tap1~2
    ScalerSetBit_EXINT(PB3_B2_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

    // Enable Adaptation
    if(GET_D4_INPUT_PIXEL_CLK() > 3000) // 3000~3400
    {
        // Enable the Vth, Tap0 Adaptation Loop  0x041
        ScalerSetByte_EXINT(P7D_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7D_C1_L2_DFE_EN_2, 0x41);
    }
    else if(GET_D4_INPUT_PIXEL_CLK() > 375) // 375~3000
    {
        // Enable the LE, Vth, Tap0~1 Adaptation Loop  0x043
        ScalerSetByte_EXINT(P7D_A1_L0_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7D_C1_L2_DFE_EN_2, 0x43);
    }
    else // 25~375
    {
        // Disable Adaptation Loop  0x000
        ScalerSetByte_EXINT(P7D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7D_C1_L2_DFE_EN_2, 0x00);
    }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6) &&
       (((GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)) ||
        ((GET_TMDS_RX4_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) && (GET_D4_INPUT_PIXEL_CLK() >= 2000))))
    {
        // [2] reg_en_eqen_manual_l0 = 1'b1
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~_BIT2, _BIT2);

        // [0] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(PB3_B9_LANE0_A_CDR_00, ~_BIT0, 0x00);
        ScalerSetBit_EXINT(PB3_B9_LANE0_A_CDR_00, ~_BIT0, _BIT0);

        // Waiting for FLD Lock Band
        for(ucTemp = 0; ucTemp <= 80; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }
    }
    else
#endif
    {
        // Reset Digital CDR
        ScalerSetBit_EXINT(PB3_C1_TMDS_CONT_1, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(PB3_C1_TMDS_CONT_1, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
    }

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB3_A7_CMU_07, ~_BIT7, _BIT7);

    // Waiting for CMU PLL Stable
    for(ucTemp = 0; ucTemp <= 10; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB3_F5_WD_01, ~_BIT4, _BIT4);

    // [0] en_eqen_manual = 1 --> Enable Adaptation
    ScalerSetBit_EXINT(PB3_F6_EQEN_TIMER, ~_BIT0, _BIT0);

    // Waiting for the Adaptation
    for(ucTemp = 0; ucTemp <= 40; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // Reduce Loop Gain to 1/4
    ScalerSetBit_EXINT(P7D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P7D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
    ScalerSetBit_EXINT(P7D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);

    // Waiting for the Adaptation
    for(ucTemp = 0; ucTemp <= 20; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // Enable Adaptation for High Frequency
    if(GET_D4_INPUT_PIXEL_CLK() > 3000) // 3000~3400
    {
        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB3_F6_EQEN_TIMER, ~_BIT0, 0x00);

        // Restore Loop Gain to 1
        ScalerSetBit_EXINT(P7D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(P7D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);
        ScalerSetBit_EXINT(P7D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), 0x00);

        // Enable the LE, Tap1~2 Adaptation Loop  0x06
        ScalerSetByte_EXINT(P7D_A1_L0_DFE_EN_2, 0x06);
        ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x06);
        ScalerSetByte_EXINT(P7D_C1_L2_DFE_EN_2, 0x06);

        // [0] en_eqen_manual = 1 --> Enable Adaptation
        ScalerSetBit_EXINT(PB3_F6_EQEN_TIMER, ~_BIT0, _BIT0);

        // Waiting for the Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Reduce Loop Gain to 1/4
        ScalerSetBit_EXINT(P7D_A0_L0_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
        ScalerSetBit_EXINT(P7D_B0_L1_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);
        ScalerSetBit_EXINT(P7D_C0_L2_DFE_EN_1, ~(_BIT5 | _BIT4), _BIT5);

        // Waiting for the Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }
    }

#if((_D3_INPUT_PORT_TYPE != _D3_DUAL_DVI_PORT) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6) // MHL Mode
    {
        // Disable Adaptation Loop
        ScalerSetByte_EXINT(P7D_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7D_C1_L2_DFE_EN_2, 0x00);

        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB3_F6_EQEN_TIMER, ~_BIT0, 0x00);

        // [5] reg_adp_eq_off = 1'b0 -->  Disable Analog CDR DFE Adaptation
        ScalerSetBit_EXINT(PB3_F9_LANE0_A_CDR_03, ~_BIT5, _BIT5);

        // [2] reg_en_eqen_manual_l0 = 1'b0
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~_BIT2, 0x00);
    }
    else
#endif
    {
        // Disable the Vth Adaptation Loop
        ScalerSetBit_EXINT(P7D_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7D_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7D_C1_L2_DFE_EN_2, ~_BIT6, 0x00);
    }
#elif(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)  // D4 = Dual DVI Sub-Port
    {
        // Check Whether Clock > 1G for High Speed
        if(GET_D4_INPUT_PIXEL_CLK() > 1000)
        {
            // Start to Record Tap0 Max/Min
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~_BIT0, _BIT0);

            // Waiting for DFE Adaptation
            for(ucTemp = 0; ucTemp <= 200; ucTemp++)
            {
                Delay5us_EXINT(g_ucDelay5usN);
            }

            // Stop to Record Tap0 Max/Min
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~_BIT0, 0x00);

            // Read Out DFE VTH Value
            ScalerSetBit_EXINT(P7D_F0_COEF_1, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Lane0 VTH adapt Value
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucVth[0] = ScalerGetByte_EXINT(P7D_F1_COEF_2);

            // Lane1 VTH adapt Value
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucVth[1] = ScalerGetByte_EXINT(P7D_F1_COEF_2);

            // Lane2 VTH adapt Value
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucVth[2] = ScalerGetByte_EXINT(P7D_F1_COEF_2);

            // Read Back Tap0 Max
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Read Back Lane0 Tap0
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucTap0Max[0] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Read Back Lane1 Tap0
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucTap0Max[1] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Read Back Lane2 Tap0
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucTap0Max[2] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Read Back LE Max
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

            // Read Back Lane0 LE
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
            pucLEMax[0] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Read Back Lane0 LE
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
            pucLEMax[1] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Read Back Lane2 LE
            ScalerSetBit_EXINT(P7D_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
            pucLEMax[2] = ScalerGetByte_EXINT(P7D_F3_COEF_4);

            // Check Whether DFE is Abnormal
            if(((pucTap0Max[0] == 21) && (pucVth[0] == 0)) ||
               ((pucTap0Max[1] == 21) && (pucVth[1] == 0)) ||
               ((pucTap0Max[2] == 21) && (pucVth[2] == 0)))
            {
                // DFE Shows that Port 4 Has No Signal
            }
            // Check Whether LE_Max > 10 for Long Cable
            else if((pucLEMax[0] > 8) || (pucLEMax[1] > 8) || (pucLEMax[2] > 8))
            {
                // Disable Lane1 Adaptation
                ScalerSetByte_EXINT(P7D_B1_L1_DFE_EN_2, 0x00);

                if(pucLEMax[2] > pucLEMax[0])
                {
                    pucLEMax[1] = pucLEMax[2];
                }
                else
                {
                    pucLEMax[1] = pucLEMax[0];
                }

                if(pucTap0Max[2] > pucTap0Max[0])
                {
                    pucTap0Max[1] = pucTap0Max[2];
                }
                else
                {
                    pucTap0Max[1] = pucTap0Max[0];
                }

                // Reload Lane1 Tap0/LE
                ScalerSetByte_EXINT(P7D_B4_L1_INIT_2, pucTap0Max[1]);
                ScalerSetByte_EXINT(P7D_B5_L1_INIT_3, pucLEMax[1]);

                // Reload Lane1 Tap0/LE
                ScalerSetBit_EXINT(P7D_BA_L1_INIT_8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
                ScalerSetBit_EXINT(P7D_BA_L1_INIT_8, ~(_BIT1 | _BIT0), 0x00);
            }
        }
    }
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT) // MHL 2.0 ACDR
    if((ScalerGetBit_EXINT(PB3_A0_CMU_00, _BIT6) == _BIT6) &&
       (((GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)) ||
        ((GET_TMDS_RX4_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) && (GET_D4_INPUT_PIXEL_CLK() >= 2000))))
    {
        // [4] en_data_manual_l0 = 1 --> Enable Dataout for Lane0
        ScalerSetBit_EXINT(PB3_FF_LANE0_A_CDR_09, ~_BIT4, _BIT4);
    }
    else
#endif
    {
        // [0] en_data_manual = 1 --> Enable Dataout
        ScalerSetBit_EXINT(PB3_F7_DATA_TIMER, ~_BIT0, _BIT0);
    }

    // Reset PHY -> MAC Interface
    ScalerSetBit_EXINT(P73_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P73_A7_TMDS_PWDCTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset HDMI 3 Channel FIFO
    ScalerSetBit_EXINT(P73_B0_TMDS_CHANNEL_FIFO, ~_BIT6, _BIT6);

    // HDMI 3 Channel FIFO Global Enable
    ScalerSetBit_EXINT(P73_B0_TMDS_CHANNEL_FIFO, ~(_BIT7 | _BIT6), _BIT7);

    // Clear RGB Data Detection Flags
    ScalerSetBit_EXINT(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx4IntHandler_EXINT0(void) using 1
{
    BYTE pucBackUp[2];

    WORD usCount = 0;

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    bit bMHLFail = _FALSE;
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P73_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P73_C8_HDMI_APC);

    // Freq. Stable Into IRQ
    if((ScalerGetByte_EXINT(P73_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0)
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

        // Enable Freq unstable IRQ
        ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Pop up Counter Value
        ScalerSetBit_EXINT(P73_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

        usCount = (WORD)(((ScalerGetByte_EXINT(P73_ED_HDMI_FREQDET_RESULT_M) & 0x7F) << 8) | ScalerGetByte_EXINT(P73_EE_HDMI_FREQDET_RESULT_L));

        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * CLK_COUNT * _TMDS_MEASURE_CLOCK_DIVIDER / _TMDS_MEASURE_CLOCK_COUNTER
        SET_D4_INPUT_PIXEL_CLK((((DWORD)_GDI_CLK_KHZ * usCount + 50000) / 100000));

        if((GET_TMDS_RX4_PHY_SET() == _FALSE) || ((bit)ScalerTMDSRx4CheckCDRStable_EXINT0(g_usTMDSRx4ClkCount) == _FALSE))
        {
            g_usTMDSRx4ClkCount = ScalerTMDSRx4MeasureClk_EXINT0(_CLK_SOURCE_TMDS);

            // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSRx4ClkCount
            SET_TMDS_D4_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) / 100) / g_usTMDSRx4ClkCount);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR);

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                // Set HDMI/DVI switch to Auto Mode
                ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
                // Set HDMI/DVI switch to Manual Mode and Forced to HDMI
                ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif
                SET_TMDS_RX4_CLK_MODE(_TMDS_MHL_PPMODE_PHY_SETTING);

                SET_D4_INPUT_PIXEL_CLK(GET_D4_INPUT_PIXEL_CLK() * 4);
                ScalerTMDSRx4SetPhy_EXINT0();
                SET_D4_INPUT_PIXEL_CLK(GET_D4_INPUT_PIXEL_CLK() / 4);

                // Enable Packed Pixel Mode
                ScalerSetBit_EXINT(P78_A0_MHL_CTRL_00, ~_BIT1, _BIT1);

                // Check CDR Stable
                if((ScalerTMDSRx4CheckCDRStable_EXINT0(g_usTMDSRx4ClkCount) == _FALSE) || (ScalerMHLRx4DetectClkMode_EXINT0() == _FALSE))// MHL mode need modify
                {
                    SET_TMDS_RX4_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                    // TMDS_FREQ(MHz) = GDI_CLK(MHz) * 1024 / CLK_COUNT = GDI_CLK(KHz) * 1024 / (CLK_COUNT * 1024)
                    SET_D4_INPUT_PIXEL_CLK(GET_D4_INPUT_PIXEL_CLK() * 3);
                    ScalerTMDSRx4SetPhy_EXINT0();
                    SET_D4_INPUT_PIXEL_CLK(GET_D4_INPUT_PIXEL_CLK() / 3);

                    // Disable Packed Pixel Mode
                    ScalerSetBit_EXINT(P78_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                    if((ScalerTMDSRx4CheckCDRStable_EXINT0(g_usTMDSRx4ClkCount) == _FALSE) || (ScalerMHLRx4DetectClkMode_EXINT0() == _FALSE))// MHL Need modify
                    {
                        bMHLFail = _TRUE;
                    }
                }
            }
            else
            {
                SET_TMDS_RX4_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                ScalerTMDSRx4SetPhy_EXINT0();

                // Disable Packed Pixel Mode
                ScalerSetBit_EXINT(P78_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                // Set HDMI/DVI switch to Auto Mode
                ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR);
                ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            }
#else
            ScalerTMDSRx4SetPhy_EXINT0();
#endif
        }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        if(bMHLFail == _FALSE)
#endif
        {
            // Set Upper Bound (allow 1/64 freq shift)
            ScalerSetByte_EXINT(P73_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

            // Set Lower Bound
            ScalerSetByte_EXINT(P73_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

            // Release Key Calculation
            ScalerSetBit_EXINT(P73_AE_TMDS_RPS, ~_BIT1, _BIT1);

            // Reset Color Depth to 8 Bits
            SET_COLOR_DEPTH(_D4_INPUT_PORT, _COLOR_DEPTH_8_BITS);

            SET_TMDS_RX4_PHY_SET();
        }
    }

    // Freq. Unstable Into IRQ
    if((ScalerGetByte_EXINT(P73_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06)
    {
        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTMDSRx4ClkCount - ScalerTMDSRx4MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTMDSRx4ClkCount >> 6)) ||
           (abs(GET_D4_INPUT_PIXEL_CLK() - ((GET_TMDS_D4_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE(_D4_INPUT_PORT) == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH(_D4_INPUT_PORT)))) > (GET_D4_INPUT_PIXEL_CLK() >> 6)))
        {
#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
            if(ScalerTMDSRx4GetDualDVIMode_EXINT0() == _TRUE)
#endif
            {
                if((GET_TMDS_RX4_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M1) != 0)
                {
                    // Set Display M1 output force to background color and free run mode
                    ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
                }

                if((GET_TMDS_RX4_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M2) != 0)
                {
                    // Set Display M2 output force to background color and free run mode
                    ScalerSetBit_EXINT(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, ~_BIT5, _BIT5);
                }

                if((GET_TMDS_RX4_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S1) != 0)
                {
                    // Set Display S1 output force to background color and free run mode
                    ScalerSetBit_EXINT(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, ~_BIT5, _BIT5);
                }

                if((GET_TMDS_RX4_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S2) != 0)
                {
                    // Set Display S2 output force to background color and free run mode
                    ScalerSetBit_EXINT(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, ~_BIT5, _BIT5);
                }
            }
            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            // Set HDMI/DVI switch to Auto Mode
            ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR);
            ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte_EXINT(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte_EXINT(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

                // Suspend Key Calculation before load key
                ScalerSetBit_EXINT(P73_AE_TMDS_RPS, ~_BIT1, 0x00);
            }
            else
#endif
            {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte_EXINT(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte_EXINT(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte_EXINT(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte_EXINT(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            }

            // Set Lower Bound
            ScalerSetByte_EXINT(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte_EXINT(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            CLR_TMDS_RX4_PHY_SET();
        }
    }

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_60_PORT_PAGE73_HDMI_INTCR);
    ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P73_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P73_C9_HDMI_AP, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSRx4MeasureClk(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte(PB3_A1_CMU_01, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte(PB3_A1_CMU_01, 0xF7);
    }

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit(P73_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    // Start Measure
    ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        Delay5us(g_ucDelay5usN);

        if((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSRx4MeasureClk_EXINT0(BYTE ucMeasureClk) using 1
{
    BYTE ucDelayCount = 0;
    WORD usClkCount = 0;
    BYTE ucBackUp = 0;

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte_EXINT(PB3_A1_CMU_01, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte_EXINT(PB3_A1_CMU_01, 0xF7);
    }

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit_EXINT(P73_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    ucBackUp = ScalerGetByte_EXINT(P73_C8_HDMI_APC);

    // Start Measure
    ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P73_CA_HDMI_DP, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        Delay5us(g_ucDelay5usN);

        if((ScalerGetBit_EXINT(P73_CA_HDMI_DP, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_28_PORT_PAGE73_HDMI_NTX1024TR0);
    usClkCount = ((WORD)(ScalerGetByte_EXINT(P73_CA_HDMI_DP) & 0x07) << 8);

    ScalerSetByte_EXINT(P73_C9_HDMI_AP, _P73_CA_PT_29_PORT_PAGE73_HDMI_NTX1024TR1);
    usClkCount =  usClkCount | ScalerGetByte_EXINT(P73_CA_HDMI_DP);

    ScalerSetByte_EXINT(P73_C8_HDMI_APC, ucBackUp);

    return usClkCount;
}

#if(_D4_HDMI_SUPPORT == _ON)
#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Set Deep Color PLL
// Input Value  : usTMDSClkCount, ucColorDepth
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSRx4HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth)
{
    DWORD ulTMDSClkValue = 0;
    WORD usM = 0;
    BYTE ucN = 0;
    BYTE ucDivS = 0;
    BYTE ucFactor = 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Fin = TMDS_clk
    // Fref = Fin / N
    // Fvco = Fin * M / N
    // Freq = Fvco / Divs
    //
    // Restriction
    // A. BW = Kvco * Icp * R / (M * 2pi) = 700k (Band10 Kvco = 1880), R = 13k)
    // B. 300MHz < Fvco < 600MHz
    // C. (Fin / N) >= 10 * BW --> (Fin / N) >= 7MHz
    // D. YCbCr 420, Ratio = 2, other case Ratio = 1
    //
    // note 1.   According A, Icp = 2.5 ~ 20 --> 14 <= M <= 111
    // note 2.   According B and note 1. --> 3 <= (Fin / N) <= 42
    // note 3.   According C and note 2. --> 7 <= (Fin / N) <= 42
    // note 4_a. 10bit : (M / N / Divs) = (4 / 5 * Ratio) --> M = N * Divs * (4 / 5 * Ratio), N or Divs: multiple of 5
    // note 4_b. 12bit : (M / N / Divs) = (2 / 3 * Ratio) --> M = N * Divs * (2 / 3 * Ratio), N or Divs: multiple of 3
    // note 4_b. 16bit : (M / N / Divs) = (1 / 2 * Ratio) --> M = N * Divs * (1 / 2 * Ratio), N or Divs: multiple of 2
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // TMDS_clk, unit:kHz
    ulTMDSClkValue = (DWORD)_GDI_CLK_KHZ * 1024 / usTMDSClkCount;

    DebugMessageRx4("TMDS clk", ulTMDSClkValue);
    DebugMessageRx4("Color Depth", ucColorDepth);

    switch(ucColorDepth)
    {
        case _COLOR_DEPTH_10_BITS:

            ucFactor = 5;

            break;

        case _COLOR_DEPTH_12_BITS:

            ucFactor = 3;

            break;

        case _COLOR_DEPTH_16_BITS:

            ucFactor = 2;

            break;

        default:

            return _FALSE;
    }

    // N <= (Fin / 7)
    PDATA_WORD(0) = (ulTMDSClkValue / 7000);

    if(PDATA_WORD(0) < 2)
    {
        return _FALSE;
    }
    else if(PDATA_WORD(0) >= ucFactor)
    {
        // N: Multiple of factor
        PDATA_WORD(0) -= (PDATA_WORD(0) % ucFactor);
    }
    else if(PDATA_WORD(0) > 255)
    {
        // N: Multiple of factor
        PDATA_WORD(0) = 255 - (255 % ucFactor);
    }

    ucN = PDATA_WORD(0);

    // for differenct Divs, find suitable Divs and M
    for(pData[15] = 0; pData[15] <= 254; pData[15] += 2)
    {
        // N or Divs: Multiple of factor
        if(((ucN % ucFactor) == 0x00) || ((pData[15] % ucFactor) == 0x00))
        {
            usM = (WORD)ucN * ((pData[15] == 0) ? 1 : pData[15]) * (ucFactor - 1) / ucFactor;

            // Fvco = Fin * M / N
            PDATA_DWORD(0) = (ulTMDSClkValue * usM / ucN);

            if((PDATA_DWORD(0) >= 300000) && (PDATA_DWORD(0) <= 600000))
            {
                ucDivS = ((pData[15] == 0) ? 1 : pData[15]);
                break;
            }
        }

        if((pData[15] == 254) && (ucDivS == 0))
        {
            DebugMessageRx4("4. PLL Setting Error", 0);
            return _FALSE;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // Precise formula of Chrage Pump Current depends on DPM, resistor, and band.                   //
    // If VCO band = 'b00, Icp = (700 * M * 2 * pi) / (778 * 0x01C1[7:5]).                          //
    // If VCO band = 'b01, Icp = (700 * M * 2 * pi) / (1340 * 0x01C1[7:5]).                         //
    // If VCO band = 'b10, Icp = (700 * M * 2 * pi) / (1880 * 0x01C1[7:5]).                         //
    // If VCO band = 'b11, Icp = (700 * M * 2 * pi) / (2340 * 0x01C1[7:5]).                         //
    // 700: DPLL max frequency design target is 700MHz; 778: Frequency curve in band00 is 778MHz.   //
    // Assume DPLL_M=0x13, DPM=0x13+2=21; DPN=2; reg_dpll_vcomd='b01; reg_dpll_rs[2:0]='b011;       //
    // Icp = (700 * 21 * 2 * 3.14) / (1340 * 13)                                                    //
    //////////////////////////////////////////////////////////////////////////////////////////////////

    // Set VCO resister = 3b'011(13K), Capacitor = 2b'11(66pF) (Analog DIC suggust)
    ScalerSetBit(P6D_BE_MN_SCLKG_PLL_CHP, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

    // BW = Kvco * Icp * R / (M * 2pi) = 700k --> Icp = M * BW * 2pi / Kvco / R
    PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / _PLL_VCO_BAND_10 / ((7 + (ScalerGetBit(P6D_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);
    pData[5] = (PDATA_WORD(1) + 25) / 50;
    pData[5] -= ((pData[5] == 0) ? 0 : 1);

    if(pData[5] > 0x07)
    {
        pData[5] = 0x07;
    }

    DebugMessageRx4("Deep Color Charge Pump icp =", pData[5]);

    // DPPLL Power Down
    ScalerSetByte(P6D_BD_MN_SCLKG_PLL_PWR, 0x80);

    // Disable M/N Tracking
    ScalerSetBit(P6D_A7_MN_SCLKG_TRK_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set PLL Charge Pump Current
    ScalerSetBit(P6D_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(P6D_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(P6D_A3_MN_SCLKG_DIVS, (ucDivS >> 1));

    // Set DPPLL Div_O.
    ScalerSetBit(P6D_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), (0 & (_BIT1 | _BIT0)));

    // Offset Value Setting
    ScalerSetByte(P6D_A6_MN_SCLKG_OFFS_L, 0);
    ScalerSetByte(P6D_A5_MN_SCLKG_OFFS_M, 0);
    ScalerSetBit(P6D_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P6D_A7_MN_SCLKG_TRK_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Enable phase swallow
    ScalerSetBit(P6D_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(P6D_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (HIBYTE(usM - 2) & 0x03));
    ScalerSetByte(P6D_A1_MN_SCLKG_DIVM, LOBYTE(usM - 2));

    // Set DPPLL N Code
    ScalerSetByte(P6D_A2_MN_SCLKG_DIVN, (ucN - 2));

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    ScalerSetBit(P6D_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

    // Load offset value
    ScalerSetBit(P6D_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(P6D_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(P6D_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(P6D_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);

    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(P6D_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(P6D_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(P6D_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // Check VCO Band is '10
    if(ScalerGetBit(P6D_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) != _BIT5)
    {
        switch(ScalerGetBit(P6D_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) >> 4)
        {
            case 00:

                PDATA_WORD(0) = _PLL_VCO_BAND_00;
                break;

            case 01:

                PDATA_WORD(0) = _PLL_VCO_BAND_01;
                break;

            case 10:

                PDATA_WORD(0) = _PLL_VCO_BAND_10;
                break;

            case 11:

                PDATA_WORD(0) = _PLL_VCO_BAND_11;
                break;

            default:
                PDATA_WORD(0) = _PLL_VCO_BAND_10;
                break;
        }

        PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / PDATA_WORD(0) / ((7 + (ScalerGetBit(P6D_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);

        DebugMessageRx4("4. reset Icp", PDATA_WORD(1));

        pData[5] = (PDATA_WORD(1) + 25) / 50;
        pData[5] -= ((pData[5] == 0) ? 0 : 1);

        if(pData[5] > 0x07)
        {
            pData[5] = 0x07;
        }

        // Set PLL Charge Pump Current
        ScalerSetBit(P6D_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

        DebugMessageRx4("4. VCO is not band10, reset Icp", pData[5]);
    }

    return _TRUE;
}
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)

#endif // End of #if(_D4_HDMI_SUPPORT == _ON)


#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSRx4TMDSScanInputPort(BYTE ucInputType)
{
    BYTE ucTMDSType = _SOURCE_NONE;

    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

    ucInputType = ucInputType;

    if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        return _SOURCE_NONE;
    }

    if(GET_TMDS_RX4_PHY_SET() == _TRUE)
    {
        // Set DIGITAL_PORT_SWITCH Flag for MHL
        SET_DIGITAL_PORT_SWITCH_TO_D4();

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        if((ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE) ||
           ((GET_D4_TMDS_MODE() == _TMDS_MHL_MODE) && (ScalerMHLRx4DetectClkMode() == _FALSE)))

#else
        if(ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE)

#endif
        {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
            }
            else
#endif
            {
#if(_TMDS_LOW_SPEED_PORT_SPEED_LIMIT == _OFF)
                // Set Upper Bound
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
#else
                ScalerSetByte(P73_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
                ScalerSetByte(P73_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOW_SPEED_UPPER_BOUND));
#endif
            }

            // Set Lower Bound
            ScalerSetByte(P73_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte(P73_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Set Stable Time (0x7F = about 5ms)
            ScalerSetByte(P73_EC_HDMI_FREQDET_STABLE, 0x7F);

            CLR_TMDS_RX4_PHY_SET();

            // Disable Freq. Unstable IRQ
            ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Reset Freq. Detect Counter
            ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit(P73_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit(P73_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            return _SOURCE_NONE;
        }

        DebugMessageRx4("9. Freq Check Pass => Pixel Clock", GET_D4_INPUT_PIXEL_CLK());

        // Clear RGBHV Flag
        ScalerSetBit(P73_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Info Packet SRAM
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P73_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P73_CC_HDMI_GPVS, ~_BIT5, _BIT5);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        // Clear DRR flag
        CLR_FREESYNC_ENABLED();

        // Clear SPD infoframe
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_00_PORT_PAGE73_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
#endif

        if(ScalerTMDSRx4FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx4("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, _BIT1);
#endif

#if(_HDMI_FROM_DVI_CONNECT == _OFF)
            if(GET_PORT_TYPE(ucInputType) == _PORT_DVI)
            {
                return _SOURCE_NONE;
            }
#endif
            ucTMDSType = _SOURCE_HDMI;
        }
        else
        {
#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P73_C3_HDCP_AP, _P73_C4_PT_40_PORT_PAGE73_BCAPS, ~_BIT1, 0x00);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
            {
                ucTMDSType = _SOURCE_HDMI;
            }
            else
#endif
            {
                ucTMDSType = _SOURCE_DVI;
            }
        }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
        // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
        if(((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
           !(ScalerGetBit(P73_A9_TMDS_ABC0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)))
        {
            return _SOURCE_NONE;
        }
#endif

        ucTMDSVideoDataType = ScalerTMDSRx4TMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageRx4("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ucTMDSType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
            }
            else
            {
                return _SOURCE_NONE;
            }
#else
            return _SOURCE_NONE;
#endif
        }
        else if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_RGBHV)
        {
            // Enable DE Only Mode
            ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

        // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
        // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
        ScalerSetBit(P7D_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7D_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit(P7D_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

#if(_D4_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx4HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx4HdmiVideoSetting();

            SET_COLOR_DEPTH(_D4_INPUT_PORT, ScalerTMDSRx4HdmiGetColorDepth());

            if((GET_COLOR_DEPTH(_D4_INPUT_PORT) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(_D4_INPUT_PORT) != _COLOR_SPACE_YCBCR422))
            {
                DebugMessageRx4("Deep Color Mode Detected", GET_COLOR_DEPTH(_D4_INPUT_PORT));

                SET_D4_INPUT_PIXEL_CLK((GET_D4_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH(_D4_INPUT_PORT));

                if(ScalerTMDSRx4HdmiDeepColorProc(g_usTMDSRx4ClkCount) == _FALSE)
                {
                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, _BIT7);
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(ScalerTMDSRx4HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
            {
                SET_HDMI_FREESYNC_ENABLED();

                // Get SPD Free Sync Vfreq Max
                g_usFREESYNCVFreq = (WORD)ScalerTMDSRx4HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;

                // Disable DE Only Mode
                ScalerSetBit(P73_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif
        }
        else
        {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            // Guard Band reference disable for data remapping
            ScalerSetBit(P78_B2_MHL_CTRL_12, ~_BIT7, 0x00);
#endif

            CLR_HDMI_RX4_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX4_GCP_RECEIVED();

            // Disable All WD when DVI
            ScalerTMDSRx4HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            ScalerTMDSRx4DviVideoSetting();

            SET_COLOR_DEPTH(_D4_INPUT_PORT, _COLOR_DEPTH_8_BITS);

            // Turn off Deep Color Block
            ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx4DviVideoSetting();

        SET_COLOR_DEPTH(_D4_INPUT_PORT, _COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P73_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_30_PORT_PAGE73_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_80_PORT_PAGE73_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P73_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : ucSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTMDSRx4TMDSStableDetect(BYTE ucSourceType)
{
    // CLR SCL/SDA Toggle Flag
    CLR_TMDS_RX4_DDC_DETECTED();

    if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        DebugMessageRx4("Rx4 HPD Toggle!!", 0);
        return _FALSE;
    }

    if(ScalerTMDSRx4CheckCDRStable(g_usTMDSRx4ClkCount) == _FALSE)
    {
        DebugMessageRx4("CDR Unstable!!", ucSourceType);
        return _FALSE;
    }

    if(ScalerGetBit(P73_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx4("TMDS Clock Output has been disable", ucSourceType);
        return _FALSE;
    }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if((GET_TMDS_RX4_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) ||
       ((GET_TMDS_RX4_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING) && (ucSourceType == _SOURCE_DVI)))
#endif
    {
        if(ucSourceType == _SOURCE_HDMI)
        {
            if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == 0x00)
            {
                DebugMessageRx4("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
        else
        {
            if(ScalerGetBit(P73_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx4("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }

    if(GET_TMDS_RX4_Z0_ASSERTED() == _TRUE)
    {
        if((ScalerGetBit(P73_A9_TMDS_ABC0, _BIT6) == _BIT6) && (ScalerGetBit(P73_A9_TMDS_ABC0, (_BIT7 | _BIT5)) != (_BIT7 | _BIT5)))
        {
            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            CLR_TMDS_RX4_Z0_ASSERTED();

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

            SET_TMDS_RX3_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            CLR_TMDS_RX3_Z0_ASSERTED();
#endif

            DebugMessageRx4("7. HDCP Abnormal !!!!!", 0);

            // MHL mode of MHL PORT will not return FALSE
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
        }
        else if((ScalerGetBit(P73_A9_TMDS_ABC0, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)))
        {
            CLR_TMDS_RX4_Z0_ASSERTED();

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

            CLR_TMDS_RX3_Z0_ASSERTED();
#endif

            DebugMessageRx4("7. HDCP Normal", 0);
        }
    }

#if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)
    if(ucSourceType == _SOURCE_DVI)
    {
        if(GET_TMDS_RX4_RGBHV_DETECTING() == _FALSE)
        {
            // TMDS Video Detected
            if(ScalerTMDSRx4TMDSVideoDetect(_NOT_WAIT) != _TMDS_VIDEO_DATA_RGBHV)
            {
                DebugMessageRx4("TMDS Video format changed", ucSourceType);

#if(_DVI_DE_ONLY_SUPPORT == _OFF)
                return _FALSE;
#endif
            }
        }
    }
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT)

#if(_D4_HDMI_SUPPORT == _ON)

    if(ucSourceType == _SOURCE_HDMI)
    {
        if(GET_HDMI_RX4_PACKET_DETECTING() == _FALSE)
        {
            // HDMI Packet Detected
            ScalerTMDSRx4HdmiPacketDetect(_NOT_WAIT);

            if(GET_HDMI_RX4_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if(ScalerSyncTMDSRx4HdmiColorInfoChanged() == _TRUE)
                {
                    DebugMessageRx4("Color Info Changed", ucSourceType);
                    return _FALSE;
                }

                if(ScalerTMDSRx4HdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx4("Pixel Repetition Info Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if(GET_TMDS_RX4_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
#endif
                {
                    if(GET_COLOR_SPACE(_D4_INPUT_PORT) != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx4("HDMI Info Frame Not Received and not RGB", ucSourceType);
                        return _FALSE;
                    }
                }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE(_D4_INPUT_PORT) != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx4("No Quantization Range Specified", ucSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_RX4_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx4("Pixel Repetition Not Received and not Pixel repetition 0", ucSourceType);
                    return _FALSE;
                }
            }

            if((ScalerGetDataPortBit(P73_C9_HDMI_AP, _P73_CA_PT_41_PORT_PAGE73_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P73_CC_HDMI_GPVS, _BIT0) == _BIT0))
            {
                DebugMessageRx4("HDMI AVI info frame has changed", ucSourceType);
                return _FALSE;
            }

            if(GET_HDMI_RX4_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE(_D4_INPUT_PORT) != _COLOR_SPACE_YCBCR422) && (ScalerTMDSRx4HdmiGetColorDepth() != GET_COLOR_DEPTH(_D4_INPUT_PORT)))
                {
                    DebugMessageRx4("Color Depth Has Changed", GET_COLOR_DEPTH(_D4_INPUT_PORT));
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE(_D4_INPUT_PORT) != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH(_D4_INPUT_PORT) != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx4("HDMI GCP PACKET Not Received and not 8 bit", ucSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX4_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)ScalerTMDSRx4HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_SUPPORT) != GET_HDMI_FREESYNC_ENABLED())
                {
                    DebugMessageRx4("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
            else
            {
                if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
                {
                    DebugMessageRx4("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
#endif
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        if(GET_TMDS_RX4_FREESYNC_SUPPORT() != GET_FREESYNC_SUPPORT())
        {
            SET_TMDS_RX4_FREESYNC_SUPPORT(GET_FREESYNC_SUPPORT());
            SET_TMDS_RX4_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            // MHL mode of MHL PORT will not return FALSE
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
        }
#endif
    }

#endif

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)

    if(GET_TMDS_RX4_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_RX4_TOGGLE_Z0_EVENT();

        return _FALSE;
    }

#if(_D3_INPUT_PORT_TYPE == _D3_DUAL_DVI_PORT)

    if(GET_TMDS_RX3_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_RX3_TOGGLE_Z0_EVENT();

        return _FALSE;
    }
#endif

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx4HotPlugEvent(void)
{
    BYTE ucRx4Z0Status = 0;

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
    BYTE ucRx5Z0Status = 0;
#endif

    // MHL mode of MHL PORT can not pull HPD
#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE) && (GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D4_CABLE_STATUS() == _TRUE))
#endif
    {
        // Save Z0 Status
        ucRx4Z0Status = ScalerGetBit(PB3_A2_CMU_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Disable Z0
        ScalerSetBit(PB3_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        // Save Z0 Status
        ucRx5Z0Status = ScalerGetBit(PB4_A2_CMU_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Disable Z0
        ScalerSetBit(PB4_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#endif

        // ACER mode and DVI port will only toggle Z0 130ms
#if(((_D4_INPUT_PORT_TYPE == _D4_DVI_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
        if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
        {
            ScalerTimerDelayXms(130);
        }
        else
#endif
        {
            // HPD Low
            PCB_D4_HOTPLUG(_D4_HOT_PLUG_LOW);

            // wait
            if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
            {
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
            }
            else if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
            {
                ScalerTimerDelayXms(1000);
            }
            else if(GET_TMDS_RX4_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                ScalerTimerDelayXms(130);
            }
            else
            {
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
            }

            // HPD High
            PCB_D4_HOTPLUG(_D4_HOT_PLUG_HIGH);
        }

        // Restore Z0 Status
        ScalerSetBit(PB3_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucRx4Z0Status);

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        // Restore Z0 Status
        ScalerSetBit(PB4_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucRx5Z0Status);
#endif

        DebugMessageRx4("Rx4 HPD Toggle!!", 0);
    }
    else if(GET_D4_CABLE_STATUS() == _FALSE)
    {
        // DDC reset
        MCU_FE77_DDC4_DDC_CONTROL_1 |= _BIT1;
    }



#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
    if(GET_TMDS_RX4_TOGGLE_Z0_EVENT() == _TRUE)
    {
        CLR_TMDS_RX4_TOGGLE_Z0();
        CLR_TMDS_RX4_TOGGLE_Z0_EVENT();

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
        CLR_TMDS_RX5_TOGGLE_Z0();
        CLR_TMDS_RX5_TOGGLE_Z0_EVENT();
#endif
    }
#endif

    CLR_TMDS_RX4_HPD_TRIGGER_EVENT();
}

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)
//--------------------------------------------------
// Description  : Get Whehter Current Mode is Dual DVI Mode
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx4GetDualDVIMode(void)
{
    switch(ScalerGetBit(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
        case (_BIT7 | _BIT6):
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6 | _BIT5):
#endif
            return _TRUE;

        default:
            return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Get Whehter Current Mode is Dual DVI Mode in Interupt
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
BYTE ScalerTMDSRx4GetDualDVIMode_EXINT0(void) using 1
{
    switch(ScalerGetBit_EXINT(P31_03_FC_DUAL_DVI_CTRL1, (_BIT7 | _BIT6 | _BIT5)))
    {
        case (_BIT7 | _BIT6):
#if(_D2_INPUT_PORT_TYPE == _D2_DUAL_DVI_PORT)
        case (_BIT7 | _BIT6 | _BIT5):
#endif
            return _TRUE;

        default:
            return _FALSE;
    }
}
#endif

#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

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
// ID Code      : ScalerTMDSRx1.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_TMDSRX1__

#include "ScalerFunctionInclude.h"

#if(_D1_TMDS_SUPPORT == _ON)

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
StructTMDSCtrlInfo g_stTMDSRx1CtrlInfo;
WORD g_usTMDSRx1ClkCount;

BYTE g_pucTMDSRx1LEMax[3];
BYTE g_pucTMDSRx1LEMin[3];

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
BYTE g_ucTMDSRx1ClkMode = _TMDS_24BIT_PHY_SETTING;
#endif

#if(_D1_HDMI_SUPPORT == _ON)
BYTE g_ucTMDSRx1AviInfo;
#endif

EnumDisplayDataPath g_enumTMDSRx1IrqForceBackgrd;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
void ScalerTMDSRx1Initial(BYTE ucInputPort);
void ScalerTMDSRx1InterruptInitial(void);
void ScalerTMDSRx1SetDFEInitial_EXINT0(void);
void ScalerTMDSRx1SetPhy_EXINT0(void);
void ScalerTMDSRx1IntHandler_EXINT0(void);
bit ScalerTMDSRx1CheckCDRStable(WORD usClkCount);
BYTE ScalerTMDSRx1CheckCDRStable_EXINT0(WORD usClkCount);
WORD ScalerTMDSRx1MeasureClk(BYTE ucMeasureClk);
WORD ScalerTMDSRx1MeasureClk_EXINT0(BYTE ucMeasureClk);
void ScalerTMDSRx1DviVideoSetting(void);
void ScalerTMDSRx1SetPorchColor(EnumColorSpace enumColorFormat);

#if(_D1_HDMI_SUPPORT == _ON)
bit ScalerTMDSRx1HdmiDeepColorProc(WORD usTmdsClkCnt);
bit ScalerTMDSRx1HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth);
bit ScalerTMDSRx1HdmiWaitDeepColorPllLock(void);
void ScalerTMDSRx1HdmiPacketDetect(bit bWait);
void ScalerTMDSRx1HdmiPacketDetectEvent(void);
BYTE ScalerTMDSRx1HdmiGetAVIInfo(EnumAviInfoContent enumContent);
bit ScalerTMDSRx1HdmiAviPixelRepInfoChanged(void);
BYTE ScalerTMDSRx1HdmiGetColorDepth(void);
void ScalerTMDSRx1HdmiAVMuteProc(void);
void ScalerTMDSRx1HdmiWatchDog(BYTE ucWDType, bit bEnable);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
void ScalerTMDSRx1PSIntHandler_EXINT0(void);
void ScalerTMDSRx1ReadRequestProc_EXINT0(BYTE ucRROutCome);
void ScalerTMDSRx1HDMI2HPDRRIRQEnable(bit bEnable);
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
BYTE ScalerTMDSRx1HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent);
#endif
#endif

void ScalerTMDSRx1PowerSavingProc(void);
void ScalerTMDSRx1PowerOffProc(void);
void ScalerTMDSRx1FreqDetectDisable(void);
void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType);
void ScalerTMDSRx1TMDSScanInitial(BYTE ucInputPort);
bit ScalerTMDSRx1TMDSPSPreDetect(BYTE ucInputPort);
bit ScalerTMDSRx1TMDSNormalPreDetect(BYTE ucInputPort);
BYTE ScalerTMDSRx1TMDSScanInputPort(BYTE ucInputType);
BYTE ScalerTMDSRx1FormatDetect(void);
bit ScalerTMDSRx1HdcpEnabled(void);
BYTE ScalerTMDSRx1TMDSVideoDetect(bit bWait);
void ScalerTMDSRx1TMDSVideoDetectEvent(void);
bit ScalerTMDSRx1TMDSStableDetect(BYTE ucSourceType);
void ScalerTMDSRx1HotPlugEvent(void);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Initialize TMDS setting for search
// Input Value  : Current Search Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1Initial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Disable TMDS output
    ScalerSetBit(P70_A6_TMDS_OUTCTL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

    // Set HS Width(DE only) and HDCP Reference VS
    ScalerSetBit(P70_AB_TMDS_ACC2, ~(_BIT7 | _BIT6), 0x00);

    // Set TMDS Hsync/Vsync Polarity as Input Raw Polarity
    ScalerSetBit(P70_AF_TMDS_WDC, ~(_BIT3 | _BIT2), 0x00);

    // Disable C9/CA Port Auto-Inc
    ScalerSetBit(P70_C8_HDMI_APC, ~_BIT0, 0x00);

#if(_D1_HDMI_SUPPORT == _ON)

    ScalerTMDSRx1HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

    // Deep Color Mode clock and detection auto
    ScalerSetBit(P70_B8_TMDS_DPC1, ~(_BIT3 | _BIT2), _BIT2);

    // Enable BCH Detection
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_02_PORT_PAGE70_HDMI_BCHCR, ~(_BIT6 | _BIT3 | _BIT2 | _BIT1), (_BIT6 | _BIT3 | _BIT2 | _BIT1));

    // DVI mode don't disable Audio Clk
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

    // Set Video Watch Dog New Mode
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_32_PORT_PAGE70_HDMI_WDCR1, ~_BIT5, _BIT5);

    // Specify Packet Detect Type
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_43_PORT_PAGE70_HDMI_PTRSV0, _HDMI_AVI_INFO_TYPE);
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_44_PORT_PAGE70_HDMI_PTRSV1, _HDMI_GENERAL_CONTROL_TYPE);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_A4_PORT_PAGE70_HDMI_PTRSV_2, _SPD_INFO_TYPE);
#endif

    // Packet Variation Detect Disable
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_45_PORT_PAGE70_HDMI_PVGCR0, 0x00);
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_46_PORT_PAGE70_HDMI_PVGCR1, 0x00);
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_47_PORT_PAGE70_HDMI_PVGCR2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_A9_PORT_PAGE70_HDMI_PVSR_4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_AA_PORT_PAGE70_HDMI_PVGCR3, 0x00);
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_AB_PORT_PAGE70_HDMI_PVGCR4, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#if(_D1_HDMI_2_0_SUPPORT == _ON)

    if(ScalerGetBit(P70_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        // Disable HDMI 2.0 SCDC Function
        ScalerSetBit(P70_19_HDMI_CTRL_19, ~_BIT7, 0x00);

        CLR_TMDS_RX1_HIGH_SPEED_MODE();
    }

    // Disable SCDC Scrambling Status
    ScalerSetDataPortBit(P70_39_HDMI_CTRL_39, _P70_3A_PT_21_PORT_PAGE70_HDMI_SCDC_21, ~_BIT0, 0x00);

    // Set Scrambling detection SSCP Number = 8, Enable HW Auto Detect Scrambling Control Symbol
    ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT2 | _BIT1 | _BIT0));

    // Set SCDC Port not auto increase
    ScalerSetBit(P70_38_HDMI_CTRL_38, ~(_BIT4 | _BIT0), _BIT4);

    // Disable Ignore Source Transimit Read Request Enable
    ScalerSetBit(P70_1C_HDMI_CTRL_1C, ~_BIT2, 0x00);

    // Enable HDMI 2.0 Function
    ScalerSetBit(P70_00_HDMI_CTRL_00, ~_BIT0, _BIT0);

    // Enable HDMI 2.0 SCDC Module
    ScalerSetBit(P70_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

#else

    // Disable HDMI 2.0 Function
    ScalerSetBit(P70_00_HDMI_CTRL_00, ~_BIT0, 0x00);

    // Disable HDMI 2.0 SCDC Function
    ScalerSetBit(P70_19_HDMI_CTRL_19, ~_BIT7, 0x00);

#endif

#endif // End of #if(_D1_HDMI_SUPPORT == _ON)

    // Set HDCP DDC Channel
    ScalerSetBit(P70_C2_HDCP_PCR, ~(_BIT2 | _BIT1), 0x00);

    // Set HDCP DDC Debounce, TMDS Function
    ScalerSetBit(P70_AC_TMDS_Z0CC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

    // Set D1 Port HDCP Address is 0x74
    ScalerSetDataPortBit(P70_C3_HDCP_AP, _P70_C4_PT_C2_PORT_PAGE70_HDCP_SLAVE_ADD, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3A);

    // Set HDCP Feature
#if(_D1_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x81);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x83);
#else
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x81);
#endif

#else // Else of #if(_D1_HDMI_SUPPORT == _ON)

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_0)
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x01);
#elif(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_1_1)
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x03);
#else
    ScalerSetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, 0x01);
#endif

#endif // End of #if(_D1_HDMI_SUPPORT == _ON)

    // Enable New Advance Cipher Mode, Enable HDCP Module
    ScalerSetBit(P70_C0_HDCP_CR, ~(_BIT7 | _BIT0), (_BIT7 | _BIT0));

    // MAC Select to HDMI
    ScalerSetBit(PB0_00_HD_DP_SEL, ~_BIT0, _BIT0);

    // Disable HDMI MAC Global Power Down
    ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT1, 0x00);

    // Enable MAC Input
    ScalerSetBit(P70_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Set MAC Signal Swap
    ScalerSetBit(P70_A7_TMDS_PWDCTL, ~(_BIT6 | _BIT5), ((_D1_TMDS_BR_SWAP << 6) | (_D1_TMDS_PN_SWAP << 5)));

    // Auto switch to DVI when no signal
    ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT2, _BIT2);

    // Detect TMDS Format by Data Island Packet Preamble & Guard Band
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT4 | _BIT1), _BIT1);

    // Enable TMDS MAC Error Correction
    ScalerSetBit(P70_B7_TMDS_UDC2, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable MHL Mac and Set MHL MAC Signal Swap
        ScalerSetBit(P75_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), ((_D1_TMDS_PN_SWAP << 5) | _BIT0));

        // Enable New Algorithm for Packed Pixel Mode
        ScalerSetBit(P75_A1_MHL_CTRL_01, ~_BIT7, _BIT7);

        // Guard Band reference enable for data remapping
        ScalerSetBit(P75_B2_MHL_CTRL_12, ~_BIT7, _BIT7);

        // Set 24Bit Mode Threshold
        ScalerSetByte(P75_AA_MHL_CTRL_0A, 0x00);
        ScalerSetByte(P75_AB_MHL_CTRL_0B, 0x09);

        // Set PP Mode Threshold
        ScalerSetByte(P75_AC_MHL_CTRL_0C, 0x00);
        ScalerSetByte(P75_AD_MHL_CTRL_0D, 0x09);

        // Set Detection Period
        ScalerSetByte(P75_A8_MHL_CTRL_08, 0x69);
        ScalerSetByte(P75_A9_MHL_CTRL_09, 0x78);

        // Set Detection by Video Leading and Detection Period by Xtal
        ScalerSetBit(P75_A7_MHL_CTRL_07, ~(_BIT4 | _BIT3 | _BIT2 | _BIT0), _BIT2);
    }
    else
#endif
    {
        // Disable MHL Mac and Revert CDR Data Polarity
        ScalerSetBit(P75_A0_MHL_CTRL_00, ~(_BIT5 | _BIT0), 0x00);

        // Guard Band reference disable for data remapping
        ScalerSetBit(P75_B2_MHL_CTRL_12, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Initialize TMDS Interrupt Required Settings
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1InterruptInitial(void)
{
    if(ScalerGetBit(P70_E6_HDMI_FREQDET_CTRL, _BIT1) == 0x00)
    {
        CLR_TMDS_RX1_PHY_SET();
    }

    // Enable Rx_En for Clk pair Z0
    ScalerSetBit(PB0_A1_CMU_01, ~_BIT7, _BIT7);

    // Choose Measure Clk to TMDS Clk
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);

    // Set Freq. Reference Counter = 1000
    ScalerSetBit(P70_F6_HDMI_FREQDET_BOUND_H, ~(_BIT1 | _BIT0), 0x00);

    // Settings for IRQ set PHY
    // Consider using table to fill all required initial settings
    // Set pre-set threshold (225MHz * 0.01 / 26.8KHz = 0x54)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P70_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Upper Bound
        ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
        ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
    }
    else
#endif
    {
        // Set TMDS Offset = 1/32
        ScalerSetBit(P70_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Set Upper Bound
        ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
    }

    // Set Lower Bound
    ScalerSetByte(P70_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
    ScalerSetByte(P70_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

    // Set Stable Time (0x7F = about 5ms)
    ScalerSetByte(P70_EC_HDMI_FREQDET_STABLE, 0x7F);

    // Disable Freq. Unstable IRQ
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

    // Enable Freq. Stable IRQ
    ScalerSetBit(P70_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // Clear IRQ Pending Flag
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_60_PORT_PAGE70_HDMI_INTCR, ~_BIT7, _BIT7);

    // Internal IRQ Enable (Global)
    ScalerGlobalIRQControl(_ENABLE);

    EX0 = 1;

    // Start Freq. Detection
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);
}

//--------------------------------------------------
// Description  : TMDS DFE Initial Setting (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1SetDFEInitial_EXINT0(void) using 1
{
    // [7] Positive Symbol-Rate Clock
    // [6] Enable Timer Control DFE Loop
    // [5:4] Reduce Gain to 1/4
    // [3] Disable Running Length Detection
    // [2] bypass Blank out Case-3 Symbol
    ScalerSetBit_EXINT(P7A_A0_L0_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_B0_L1_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));
    ScalerSetBit_EXINT(P7A_C0_L2_DFE_EN_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5));

    if((GET_D1_INPUT_PIXEL_CLK() > 1000) && ((GET_D1_INPUT_PIXEL_CLK() < 3400)))
    {
        // [7:6] adapt_mode[1:0] = 2'b11 --> Amplitude-based Adaptation without Independent LE Loop
        ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    else
    {
        // [7:6] adapt_mode[1:0] = 2'b10 --> Amplitude-based Adaptation with Independent LE Loop
        ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~(_BIT7 | _BIT6), _BIT7);
    }

    // [5] edge_det_mode = 1 --> Edge Lag Data
    // [4] transition_only = 1 --> Only Transition Bit is Effective
    // [3] le_auto_reload = 0 --> Disable Auto-reload LE Coefficient
    // [2:0] tap1_delay[2:0] = 3'b010 --> Tap1+LE Delay 2us after Tap0
    ScalerSetBit_EXINT(P7A_E0_MODE_TIMER, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT1));

    // Set DFE Delay Time
    // Turn On LE/Tap1~6 Simultaneously
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

    if((GET_D1_INPUT_PIXEL_CLK() > 1000) && ((GET_D1_INPUT_PIXEL_CLK() < 3400)))
    {
        // Tap1 Min is LE(-24) + Tap1(-31) = -55
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        // Tap1 Min is -31
        ScalerSetBit_EXINT(P7A_E7_LIMIT_2, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    }

    // Tap2 Max is 6, Min is -6
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));
    ScalerSetBit_EXINT(P7A_E8_LIMIT_3, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT7 | _BIT6), _BIT7);

    // Tap3 Max is 1, Min is -6
    ScalerSetBit_EXINT(P7A_E9_LIMIT_4, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT5 | _BIT4));

    // Tap4 Max is 1, Min is -6
    ScalerSetBit_EXINT(P7A_EA_LIMIT_5, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT7 | _BIT6), _BIT6);
    ScalerSetBit_EXINT(P7A_EB_LIMIT_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

    // Tap0 Threshold
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT5));

    // Set Vth Max = 6, Min = 0
    ScalerSetByte_EXINT(P7A_F9_LIMIT_10, 0x60);

    // Set Vth/Servo-loop/Tap Divider
    ScalerSetByte_EXINT(P7A_EC_LOOP_DIV_1, 0xA3);

    // Tap Divider = 10 for TP2
    ScalerSetByte_EXINT(P7A_ED_LOOP_DIV_2, 0xCA);

    // [5] servo_notrans = 1'b1 --> Servo is Effective when Non-Tran
    // [4] tap0_notrans = 1'b1 --> Tap0 is Effective when Non-Tran
    ScalerSetBit_EXINT(P7A_F8_GRAY_DEC_2, ~(_BIT5 | _BIT4), (_BIT5 | _BIT4));

    // [1] De_inverse = 1'b0 --> Adapation Only for Blanking Area (Transition Maximum)
    // [0] De_brank_en = 1'b0 --> Disable Blank Function of gdi_de
    ScalerSetBit_EXINT(P7A_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), 0x00);


    /////////////////////////
    // DFE Code Initialize //
    /////////////////////////

    // Initial DFE Code
    if(GET_D1_INPUT_PIXEL_CLK() < 375)
    {
        // LE Max = 24, Initial = 4
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x84);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x84);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() < 700)
    {
        // LE Max = 24, Initial = 6
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x86);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x86);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() < 1000)
    {
        // LE Max = 24, Initial = 10
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x8A);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x8A);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x8A);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() < 3400)
    {
        // LE Max = 24, Initial = 12
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x8C);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x8C);
    }
    else
    {
        // LE Max = 20, Initial = 12
        ScalerSetByte_EXINT(P7A_A2_L0_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_B2_L1_LIMIT_INIT, 0x4C);
        ScalerSetByte_EXINT(P7A_C2_L2_LIMIT_INIT, 0x4C);
    }

    // Servo Initial = 16
    ScalerSetByte_EXINT(P7A_A3_L0_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7A_B3_L1_INIT_1, 0x90);
    ScalerSetByte_EXINT(P7A_C3_L2_INIT_1, 0x90);

    // Tap0 Initial Value = 12
    ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, 0x0C);
    ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, 0x0C);

    if((GET_D1_INPUT_PIXEL_CLK() > 1000) && (GET_D1_INPUT_PIXEL_CLK() < 3400))
    {
        // Tap1 Initial Value = 12 for Mode3 DFE
        ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, 0x0C);
        ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, 0x0C);
        ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, 0x0C);
    }
    else
    {
        // Tap1 Initial Value = 0 for Mode2 DFE
        ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, 0x00);
        ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, 0x00);
        ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, 0x00);
    }

    // Tap2 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A6_L0_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_B6_L1_INIT_4, 0x00);
    ScalerSetByte_EXINT(P7A_C6_L2_INIT_4, 0x00);

    // Tap3 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A7_L0_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7A_B7_L1_INIT_5, 0x00);
    ScalerSetByte_EXINT(P7A_C7_L2_INIT_5, 0x00);

    // Tap4 Initial Value = 0
    ScalerSetByte_EXINT(P7A_A8_L0_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7A_B8_L1_INIT_6, 0x00);
    ScalerSetByte_EXINT(P7A_C8_L2_INIT_6, 0x00);

    if(GET_D1_INPUT_PIXEL_CLK() < 1500)
    {
        // Vth Initial Value = 6
        ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, 0x06);
        ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, 0x06);
        ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, 0x06);
    }
    else
    {
        // Vth Initial Value = 4
        ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, 0x04);
        ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, 0x04);
        ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, 0x04);
    }

    // Load Intial DFE Code
    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0xFF);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0xFF);

    ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
    ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);

    // DFE Loop Normal
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_EF_RESET_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Disable All Adaptation Loop
    ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
    ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
    ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
}

//--------------------------------------------------
// Description  : TMDS Set PHY Function (EXINT0 Only)
// Input Value  : Measured Clk Count for PHY Setting
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1SetPhy_EXINT0(void) using 1
{
    BYTE ucTemp = 0;

    ///////////////
    // RX CMU EN //
    ///////////////

    // [7] cmu_en = 0 --> Disable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, 0x00);

    // [3:0] cdr_en = 4'b0000 --> Disable CDREN
    ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    if(ScalerGetBit_EXINT(PB0_A0_CMU_00, _BIT6) == _BIT6)  // MHL Mode
    {
        // [7:4] rx_en = 4'b1001 --> Enable RXEN for Lane0, 3
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

        // [5] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT5, _BIT5);

        for(ucTemp = 0; ucTemp <= 5; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [3:0] cdr_en = 4'b0001 --> Enable CDREX for Lane0
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
    {
        // [7:4] rx_en = 4'b1111 --> Enable RXEN
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // [5] sel_iblpf = 1 --> Enable Local Bias LPF
        ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT5, _BIT5);

        for(ucTemp = 0; ucTemp <= 5; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // [3:0] cdr_en = 4'b0001 ~ 4'b0011 ~ 4'b0111
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(PB0_A1_CMU_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    }


    /////////////////
    // CMU Setting //
    /////////////////

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(ScalerGetBit_EXINT(PB0_A0_CMU_00, _BIT6) == _BIT6)   // MHL Mode
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            // [7:5] rate_sel = 3'b001 --> 2250MHz ~ 3000MHz
            ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

            // [7:5] SEL_DIV = 3'b001 --> 2250MHz ~ 3000MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x30);

            // [7:4] CMU_SEL_PUMP_I = 4'b0010 --> Icp = 7.5uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x27);

            // [7:0] N_CODE = 8'b0100 1100 --> 36 + 4 = 40
            ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x24);
        }
        else  // MHL 24bit Mode
        {
            // [7:4] CMU_SEL_PUMP_I = 4'b0100 --> Icp = 12.5uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x47);

            if((GET_D1_INPUT_PIXEL_CLK() >= 700) && (GET_D1_INPUT_PIXEL_CLK() < 1125))
            {
                // [7:5] rate_sel = 3'b010 --> 750MHz ~ 1125MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

                // [7:5] SEL_DIV = 3'b010 --> 750MHz ~ 1125MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x50);

                // [7:0] N_CODE = 8'b0011 1000 --> 56 + 4 = 60
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x38);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 1125) && (GET_D1_INPUT_PIXEL_CLK() < 1500))
            {
                // [7:5] rate_sel = 3'b010 --> 1125MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

                // [7:5] SEL_DIV = 3'b010 --> 1125MHz ~ 1500MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x51);

                // [7:0] N_CODE = 8'b0111 0100 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x74);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 1500) && (GET_D1_INPUT_PIXEL_CLK() < 2360))
            {
                // [7:5] rate_sel = 3'b001 --> 1500MHz ~ 2250MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [7:5] SEL_DIV = 3'b001 --> 1500MHz ~ 2250MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b10 --> /4
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x32);

                // [7:0] N_CODE = 8'b0111 0100 --> 116 + 4 = 120
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x74);
            }
        }
    }
    else     // HDMI Mode
#endif
    {
#if(_D1_HDMI_2_0_SUPPORT == _ON)
        if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
        {
            // [7:5] rate_sel = 3'b000 --> 3400MHz ~ 6000MHz
            ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // [7:5] SEL_DIV = 3'b000 --> 3400MHz ~ 6000MHz
            // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
            // [1:0] CMU_SELPREDIV = 2'b00 --> /1
            ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x10);

            // [7:4] CMU_SEL_PUMP_I = 4'b0101 --> Icp = 15uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x57);

            // Digital CDR Ref Clock = Analog CDR / 20
            ScalerSetBit_EXINT(PB0_AE_CDR_05, ~_BIT0, 0x00);
            ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT1, _BIT1);

            // [7:0] N_CODE = 8'b0001 0000 --> 16 + 4 = 20
            ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x10);
        }
        else
#endif
        {
            // [7:4] CMU_SEL_PUMP_I = 4'b1010 --> Icp = 27.5uA
            // [3:1] CMU_SEL_RI = 3'b011 --> Rs = 12KOhm
            // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
            ScalerSetByte_EXINT(PB0_A4_CMU_04, 0xA6);

            if((GET_D1_INPUT_PIXEL_CLK() >= 187) && (GET_D1_INPUT_PIXEL_CLK() < 375))
            {
                // [7:5] rate_sel = 3'b100 --> 187.5MHz ~ 375MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

                // [7:5] SEL_DIV = 3'b100 --> 187.5MHz ~ 375MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x90);

                // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x4C);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 375) && (GET_D1_INPUT_PIXEL_CLK() < 750))
            {
                // [7:5] rate_sel = 3'b011 --> 375MHz ~ 750MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT6 | _BIT5));

                // [7:5] SEL_DIV = 3'b011 --> 375MHz ~ 750MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x71);

                // [7:0] N_CODE = 8'b0100 1100 --> 76 + 4 = 80
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x4C);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 750) && (GET_D1_INPUT_PIXEL_CLK() < 1500))
            {
                // [7:5] rate_sel = 3'b010 --> 750MHz ~ 1500MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

                // [7:5] SEL_DIV = 3'b010 --> 750MHz ~ 1500MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b01 --> /2
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x51);

                // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x24);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 1500) && (GET_D1_INPUT_PIXEL_CLK() < 3000))
            {
                // [7:5] rate_sel = 3'b001 --> 1500MHz ~ 3000MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT5);

                // [7:5] SEL_DIV = 3'b001 --> 1500MHz ~ 3000MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b10 --> /4
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x32);

                // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x24);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 3000) && (GET_D1_INPUT_PIXEL_CLK() < 3400))
            {
                // [7:5] rate_sel = 3'b000 --> 3000MHz ~ 3400MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [7:5] SEL_DIV = 3'b000 --> 3000MHz ~ 3400MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b11 --> Determined by CMU_PREDIVN
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x13);

                // [4:1] CMU_PREDIVN = 4'b0110 --> /8 (N+2 Divider)
                ScalerSetBit_EXINT(PB0_A8_CMU_08, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT2));

                // [7:0] N_CODE = 8'b0010 1000 --> 36 + 4 = 40
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x24);
            }
            else if((GET_D1_INPUT_PIXEL_CLK() >= 3400) && (GET_D1_INPUT_PIXEL_CLK() < 6300))
            {
                // [7:5] rate_sel = 3'b000 --> 3400MHz ~ 6000MHz
                ScalerSetBit_EXINT(PB0_DB_ST_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

                // [7:5] SEL_DIV = 3'b000 --> 3400MHz ~ 6000MHz
                // [4:2] CMU_PI_I_SEL = 3'b100 --> 15.625uA
                // [1:0] CMU_SELPREDIV = 2'b00 --> /1
                ScalerSetByte_EXINT(PB0_A3_CMU_03, 0x10);

                // [7:4] CMU_SEL_PUMP_I = 4'b0101 --> Icp = 15uA
                // [3:1] CMU_SEL_RI = 3'b010 --> Rs = 10KOhm
                // [0] CMU_SEL_CP = 1'b1 --> Cp = 2pF
                ScalerSetByte_EXINT(PB0_A4_CMU_04, 0x55);

                // Digital CDR Ref Clock = Analog CDR / 20
                ScalerSetBit_EXINT(PB0_AE_CDR_05, ~_BIT0, 0x00);
                ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT1, _BIT1);

                // [7:0] N_CODE = 8'b0100 1100 --> 16 + 4 = 20
                ScalerSetByte_EXINT(PB0_F2_SDM_01, 0x10);
            }
        }
    }

    // [5] CMU_BYPASS_PI = 1'b1 --> Integer N PLL
    // [4] cmu_en_awdog = 1'b0 --> Disable CMU WatchDog
    // [3] CMU_CKSEL = 1'b1 --> Ref. TMDS Clock
    // [2] cmu_sel_d4 = 1'b0 --> CMU Feedback Loop Divider = 1
    ScalerSetBit_EXINT(PB0_A5_CMU_05, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT3));

    // [7] BYPASS_PI = 1'b1 --> Use Integer N_CODE
    // [5] N_CODE[8] = 1'b0 --> N = N_CODE + 4
    ScalerSetBit_EXINT(PB0_F1_SDM_00, ~(_BIT7 | _BIT5), _BIT7);

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit_EXINT(PB0_F4_WD_00, ~_BIT0, 0x00);


    /////////////////
    // CDR Setting //
    /////////////////

    if((GET_D1_INPUT_PIXEL_CLK() >= 2500) && (GET_D1_INPUT_PIXEL_CLK() < 3000))
    {
        // [3:0] KD = 4'b1111 --> KD = 1
        ScalerSetBit_EXINT(PB0_CC_ERROR_COUNT_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    }
    else
    {
        // [3:0] KD = 4'b0000 --> KD = 0
        ScalerSetBit_EXINT(PB0_CC_ERROR_COUNT_0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    }

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(ScalerGetBit_EXINT(PB0_A0_CMU_00, _BIT6) == _BIT6) // MHL Mode
    {
        // Check if Packed Pixel Mode
        if(GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
        {
            // KI = 3'b010 --> KI = 1/8
            ScalerSetBit_EXINT(PB0_D4_KI_0, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

            // KP = 0x33 --> KP = 12.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x33);
        }
        else
        {
            // KI = 3'b000 --> KI = 0
            ScalerSetBit_EXINT(PB0_D4_KI_0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

            // KP = 0x2F --> KP = 11.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x2F);
        }
    }
    else   // HDMI Mode
#endif
    {
        // KI = 3'b000 --> KI = 0
        ScalerSetByte_EXINT(PB0_D4_KI_0, 0x00);
        ScalerSetByte_EXINT(PB0_D5_KI_1, 0x00);

        if(GET_D1_INPUT_PIXEL_CLK() < 2500)
        {
            // KP = 0x0F --> KP = 3.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x0F);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x0F);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x0F);
        }
        else if((GET_D1_INPUT_PIXEL_CLK() >= 2500) && (GET_D1_INPUT_PIXEL_CLK() < 3000))
        {
            // KP = 0x2D --> KP = 11.25
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x2D);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x2D);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x2D);
        }
        else if(GET_D1_INPUT_PIXEL_CLK() < 3400)
        {
            // KP = 0x17 --> KP = 5.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x17);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x17);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x17);
        }
        else
        {
            // [5:4] reg_cdr_kvco = 2'b01 --> Analog CDR KVCO = 550M/v
            ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~(_BIT5 | _BIT4), _BIT4);

            // [4:2] reg_sel_cdr_res = 3'b011 --> Analog CDR Rs = 4K
            ScalerSetBit_EXINT(PB0_FD_LANE0_A_CDR_07, ~(_BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

            // [3:0] reg_cdr_cp_in = 4'b0010 --> Analog CDR Icp = 7.5uA
            ScalerSetBit_EXINT(PB0_FE_LANE0_A_CDR_08, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            // KP = 0x07 --> KP = 1.75
            ScalerSetByte_EXINT(PB0_D6_KP_0, 0x07);
            ScalerSetByte_EXINT(PB0_D7_KP_1, 0x07);
            ScalerSetByte_EXINT(PB0_D8_KP_2, 0x07);
        }
    }


    /////////////////////
    // Rx Misc Setting //
    /////////////////////

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

    // Load DFE Initial Code
    ScalerTMDSRx1SetDFEInitial_EXINT0();

    // [7:5] LE_lowgain_highboost = 1 --> LE HighBoost Mode
    ScalerSetBit_EXINT(PB0_A8_CMU_08, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

    // [0] Tap2~6 Adaptation Revise
    ScalerSetBit_EXINT(PB0_B2_EQ_00, ~_BIT0, 0x00);

    if(GET_D1_INPUT_PIXEL_CLK() < 2000)
    {
        // [4] SEL_DFE_DELAY = 1'b1 --> Increase DFE Delay
        ScalerSetBit_EXINT(PB0_A6_CMU_06, ~_BIT4, _BIT4);
    }
    else
    {
        // [4] SEL_DFE_DELAY = 1'b0 --> Normal DFE Delay
        ScalerSetBit_EXINT(PB0_A6_CMU_06, ~_BIT4, 0x00);
    }

    if(GET_D1_INPUT_PIXEL_CLK() < 2500)
    {
        // [7:5] LE_ISEL = 3'b000
        // [4:2] LE_RLSEL = 3'b011
        ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
    else if((GET_D1_INPUT_PIXEL_CLK() >= 2500) && (GET_D1_INPUT_PIXEL_CLK() < 3400))
    {
        // [7:5] LE_ISEL = 3'b010
        // [4:2] LE_RLSEL = 3'b001
        ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT2));
    }
    else if((GET_D1_INPUT_PIXEL_CLK() >= 3400) && (GET_D1_INPUT_PIXEL_CLK() < 6300))
    {
        // [7:5] LE_ISEL = 3'b011
        // [4:2] LE_RLSEL = 3'b000
        ScalerSetBit_EXINT(PB0_A9_CMU_09, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT6 | _BIT5));
    }


    //////////////
    // K Offset //
    //////////////

    // Enable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB0_B0_CDR_07, ~_BIT1, _BIT1);

    // [2] Enable Foreground Calibration Auto Mode
    ScalerSetBit_EXINT(PB0_AD_CDR_04, ~_BIT2, _BIT2);

    // [5] Toggle Foreground Calibration
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, _BIT5);
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, 0x00);
    ScalerSetBit_EXINT(PB0_AA_CDR_01, ~_BIT5, _BIT5);

    // Waiting for K Offset
    for(ucTemp = 0; ucTemp <= 20; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }


    /////////////////////
    // Adaptation Loop //
    /////////////////////

    // Disable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB0_B0_CDR_07, ~_BIT1, 0x00);

    // [7] cmu_en = 1'b1 --> Enable CMU PLL
    ScalerSetBit_EXINT(PB0_A7_CMU_07, ~_BIT7, _BIT7);

    // Enable Tap1~4
    ScalerSetBit_EXINT(PB0_B2_EQ_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT5 | _BIT4 | _BIT3 | _BIT2));

    // Enable Adaptation
    if(GET_D1_INPUT_PIXEL_CLK() > 3400)  // 3400~6000 Analog CDR
    {
        // [4] reg_en_data_manual_l0 = 1'b0
        // [3] reg_bypass_data_rdy_l0 = 1'b0
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), 0x00);

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // [6] xtal_en = 0 --> FLD Reference Input Clock
        // [5] reg_adp_eq_off = 1'b0 --> Enable Analog CDR DFE Adaptation
        // [4] reg_auto_mode = 1'b1 --> FLD Select Auto Mode
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~(_BIT6 | _BIT5 | _BIT4), _BIT4);

        // [0] en_wide_temp = 1'b1
        ScalerSetBit_EXINT(PB0_AB_CDR_02, ~_BIT0, _BIT0);

        // [0] reg_acdr_l0_en = 1'b1 --> Enable Lane0 ACDR
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~_BIT0, _BIT0);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
        {
            // Analog CDR Auto FLD Counter
            ScalerSetByte_EXINT(PB0_FA_LANE0_A_CDR_04, 0xF9);
            ScalerSetByte_EXINT(PB0_FB_LANE0_A_CDR_05, 0x3E);
            ScalerSetByte_EXINT(PB0_FC_LANE0_A_CDR_06, 0x85);
        }
        else
#endif
        {
            // Analog CDR Auto FLD Counter
            ScalerSetByte_EXINT(PB0_FA_LANE0_A_CDR_04, 0xA0);
            ScalerSetByte_EXINT(PB0_FB_LANE0_A_CDR_05, 0xA0);
            ScalerSetByte_EXINT(PB0_FC_LANE0_A_CDR_06, 0x05);
        }

        // [0] en_clkout_manual = 1'b1 --> Enable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

        // [7] reg_en_ana_cdr = 1'b1 --> Enable Analog CDR
        // [6] reg_en_vco_lpf = 1'b0 --> Disable Analog CDR Multi Band VCO's LPF
        // [3] reg_cp_adj_en = 1'b1 --> Enable Adjust Icp When Tracking
        // [2] reg_enhance_bias_boost = 1'b0 --> Disable Enhance LEQ Boost Bias
        // [1] reg_enhance_bias_gain = 1'b0 --> Disable Enhance LEQ Gain Bias
        // [0] reg_rstb_fsm --> Toggle for FLD reset
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT3));
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT0, _BIT0);

        // Enable the Vth, Tap0 Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);

        // Waiting for FLD Lock Band and DFE Adapt
        for(ucTemp = 0; ucTemp <= 50; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable Vth/Tap0 Adaptation
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back Tap0 Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Read Min Value of Tap0
        ScalerSetByte_EXINT(P7A_A4_L0_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Reload Min Value of Tap0
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT0, 0x00);

        // Read Back Vth
        ScalerSetByte_EXINT(P7A_F0_COEF_1, 0x00);

        // Reload Vth - 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) - 1);

        // Reload Vth
        ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);

        // Enable LE Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x80);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucTMDSRx1LEMin[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucTMDSRx1LEMax[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        if(g_pucTMDSRx1LEMax[0] < 10)
        {
            g_pucTMDSRx1LEMax[0]++;
        }
        else if(g_pucTMDSRx1LEMax[0] > 12)
        {
            g_pucTMDSRx1LEMax[0]--;
        }

        // Read Max Value of LE
        ScalerSetBit_EXINT(P7A_A2_L0_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx1LEMax[0] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_A3_L0_INIT_1, ~_BIT6, ((g_pucTMDSRx1LEMax[0] << 2) & _BIT6));

        // Reload Max Value of LE
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~_BIT7, 0x00);

        // Read Back Vth
        ScalerSetByte_EXINT(P7A_F0_COEF_1, 0x00);

        // Reload Vth + 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetByte_EXINT(P7A_A9_L0_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) + 1);

        // Reload Vth
        ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_AA_L0_INIT_8, 0x00);

        // Enable Tap0~1 Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x03);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record Tap1 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record Tap1 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Read Max Value of Tap1
        ScalerSetByte_EXINT(P7A_A5_L0_INIT_3, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Reload Max Value of Tap0~1
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT1 | _BIT0), 0x00);

        // Enable Tap3~4 Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x18);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Disable Adaptation
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);

        // [0] en_clkout_manual = 0 --> Disable Clkout
        ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, 0x00);

        // Enable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, _BIT0);

        // Enable the Vth, Tap0 Adaptation
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() > 2900) // 2900~3400
    {
        // Disable Analog CDR Mode
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT7, 0x00);

        // Disable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, 0x00);

        // Enable the Vth, Tap0 Adaptation Loop 0x041
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x41);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x41);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() > 375) // 375~2900
    {
        // Disable Analog CDR Mode
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT7, 0x00);

        // Disable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, 0x00);

        // Enable the LE, Vth, Tap0~1 Adaptation Loop 0x043
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x43);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x43);
    }
    else // 25~375
    {
        // Disable Analog CDR Mode
        ScalerSetBit_EXINT(PB0_B9_LANE0_A_CDR_00, ~_BIT7, 0x00);

        // Disable Hybrid Mode
        ScalerSetBit_EXINT(PB0_AF_CDR_06, ~_BIT0, 0x00);

        // Disable Adaptation Loop  0x000
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    }

    // Reset Digital CDR
    ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x00);
    ScalerSetByte_EXINT(PB0_C1_TMDS_CONT_1, 0x78);

    // Waiting for CMU PLL Stable
    for(ucTemp = 0; ucTemp <= 20; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    // [0] en_clkout_manual = 1 --> Enable Clkout
    ScalerSetBit_EXINT(PB0_F5_WD_01, ~_BIT4, _BIT4);

    // [0] en_eqen_manual = 1 --> Enable Adaptation
    ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, _BIT0);

    // Waiting for the Adaptation
    for(ucTemp = 0; ucTemp <= 40; ucTemp++)
    {
        Delay5us_EXINT(g_ucDelay5usN);
    }

    if(GET_D1_INPUT_PIXEL_CLK() > 3400) // 3400~6000 Analog CDR
    {
        // Start to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record Tap0 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adapation Loop
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // Read Back Tap0 Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT1);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Min Value of Tap0
        ScalerSetByte_EXINT(P7A_B4_L1_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Min Value of Tap0
        ScalerSetByte_EXINT(P7A_C4_L2_INIT_2, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Reload Min Value of Tap0
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, _BIT0);
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT0, 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT0, 0x00);

        // Read Back Vth
        ScalerSetByte_EXINT(P7A_F0_COEF_1, 0x00);

        // Reload Vth - 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) - 1);

        // Reload Vth - 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) - 1);

        // Reload Vth
        ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
        ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);

        // Enable the LE Adaptation Loop
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x80);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x80);

        // Waiting for the Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adapation Loop
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucTMDSRx1LEMin[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucTMDSRx1LEMax[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        if(g_pucTMDSRx1LEMax[1] < 10)
        {
            g_pucTMDSRx1LEMax[1]++;
        }
        else if(g_pucTMDSRx1LEMax[1] > 12)
        {
            g_pucTMDSRx1LEMax[1]--;
        }

        // Read Max Value of LE
        ScalerSetBit_EXINT(P7A_B2_L1_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx1LEMax[1] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_B3_L1_INIT_1, ~_BIT6, ((g_pucTMDSRx1LEMax[1] << 2) & _BIT6));

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        g_pucTMDSRx1LEMin[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        g_pucTMDSRx1LEMax[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        if(g_pucTMDSRx1LEMax[2] < 10)
        {
            g_pucTMDSRx1LEMax[2]++;
        }
        else if(g_pucTMDSRx1LEMax[2] > 12)
        {
            g_pucTMDSRx1LEMax[2]--;
        }

        // Read Max Value of LE
        ScalerSetBit_EXINT(P7A_C2_L2_LIMIT_INIT, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (g_pucTMDSRx1LEMax[2] & (_BIT3 | _BIT2 | _BIT1 | _BIT0)));
        ScalerSetBit_EXINT(P7A_C3_L2_INIT_1, ~_BIT6, ((g_pucTMDSRx1LEMax[2] << 2) & _BIT6));

        // Reload Max Value of LE
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT7, _BIT7);
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~_BIT7, 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~_BIT7, 0x00);

        // Read Back Vth
        ScalerSetByte_EXINT(P7A_F0_COEF_1, 0x00);

        // Reload Vth + 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        ScalerSetByte_EXINT(P7A_B9_L1_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) + 1);

        // Reload Vth + 1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        ScalerSetByte_EXINT(P7A_C9_L2_INIT_7, (ScalerGetByte_EXINT(P7A_F1_COEF_2) & 0x0F) + 1);

        // Reload Vth
        ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x40);
        ScalerSetByte_EXINT(P7A_BA_L1_INIT_8, 0x00);
        ScalerSetByte_EXINT(P7A_CA_L2_INIT_8, 0x00);

        // Enable Tap0~1 Adaptation
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x03);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x03);

        // Waiting for the Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record Tap1 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record Tap1 Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adapation Loop
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // Read Back Tap1 Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT2);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);

        // Read Max Value of Tap1
        ScalerSetByte_EXINT(P7A_B5_L1_INIT_3, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);

        // Read Max Value of Tap1
        ScalerSetByte_EXINT(P7A_C5_L2_INIT_3, ScalerGetByte_EXINT(P7A_F3_COEF_4));

        // Reload Max Value of Tap0~1
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT1 | _BIT0), 0x00);

        // Enable Tap3~4 Adaptation
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x18);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x18);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Disable All Adapation Loop
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);
    }
    else if(GET_D1_INPUT_PIXEL_CLK() > 2900) // 2900~3400
    {
        // Disable All Adapation Loop
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // Enable the LE, Tap1~2 Adaptation Loop 0x006
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x06);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x06);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x06);

        // Waiting for the Adaptation
        for(ucTemp = 0; ucTemp <= 40; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Start to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, _BIT0);

        // Waiting for DFE Adaptation
        for(ucTemp = 0; ucTemp <= 20; ucTemp++)
        {
            Delay5us_EXINT(g_ucDelay5usN);
        }

        // Stop to Record LE Max/Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~_BIT0, 0x00);

        // Disable All Adaptation Loop
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // Read Back LE Min
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT3 | _BIT1));

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        g_pucTMDSRx1LEMin[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        g_pucTMDSRx1LEMin[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        g_pucTMDSRx1LEMin[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back LE Max
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), _BIT3);

        // Read Back Lane0
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), 0x00);
        g_pucTMDSRx1LEMax[0] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane1
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT6);
        g_pucTMDSRx1LEMax[1] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Read Back Lane2
        ScalerSetBit_EXINT(P7A_F2_COEF_3, ~(_BIT7 | _BIT6), _BIT7);
        g_pucTMDSRx1LEMax[2] = ScalerGetByte_EXINT(P7A_F3_COEF_4);

        // Lane0 LEQ >= 14
        if(g_pucTMDSRx1LEMax[0] >= 14)
        {
            // Set Tap2 = 6
            ScalerSetByte_EXINT(P7A_A6_L0_INIT_4, 0x06);

            if(g_pucTMDSRx1LEMax[0] < 16)
            {
                g_pucTMDSRx1LEMax[0] = g_pucTMDSRx1LEMax[0] + 2;
            }
            else if(g_pucTMDSRx1LEMax[0] > 18)
            {
                g_pucTMDSRx1LEMax[0] = g_pucTMDSRx1LEMax[0] - 2;
            }

            // Set Max Value of LE
            ScalerSetBit_EXINT(P7A_A5_L0_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_pucTMDSRx1LEMax[0]);

            // Reload LE/Tap2
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetBit_EXINT(P7A_AA_L0_INIT_8, ~(_BIT2 | _BIT1), 0x00);
        }

        // Lane1 LEQ >= 14
        if(g_pucTMDSRx1LEMax[1] >= 14)
        {
            // Set Tap2 = 6
            ScalerSetByte_EXINT(P7A_B6_L1_INIT_4, 0x06);

            if(g_pucTMDSRx1LEMax[1] < 16)
            {
                g_pucTMDSRx1LEMax[1] = g_pucTMDSRx1LEMax[1] + 2;
            }
            else if(g_pucTMDSRx1LEMax[1] > 18)
            {
                g_pucTMDSRx1LEMax[1] = g_pucTMDSRx1LEMax[1] - 2;
            }

            // Reload Max Value of LE
            ScalerSetBit_EXINT(P7A_B5_L1_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_pucTMDSRx1LEMax[1]);

            // Reload LE/Tap2
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetBit_EXINT(P7A_BA_L1_INIT_8, ~(_BIT2 | _BIT1), 0x00);
        }

        // Lane2 LEQ >= 14
        if(g_pucTMDSRx1LEMax[2] >= 14)
        {
            // Set Tap2 = 6
            ScalerSetByte_EXINT(P7A_C6_L2_INIT_4, 0x06);

            if(g_pucTMDSRx1LEMax[2] < 16)
            {
                g_pucTMDSRx1LEMax[2] = g_pucTMDSRx1LEMax[2] + 2;
            }
            else if(g_pucTMDSRx1LEMax[2] > 18)
            {
                g_pucTMDSRx1LEMax[2] = g_pucTMDSRx1LEMax[2] - 2;
            }

            // Reload Max Value of LE
            ScalerSetBit_EXINT(P7A_C5_L2_INIT_3, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), g_pucTMDSRx1LEMax[2]);

            // Reload LE/Tap2
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));
            ScalerSetBit_EXINT(P7A_CA_L2_INIT_8, ~(_BIT2 | _BIT1), 0x00);
        }

        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);
    }

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(ScalerGetBit_EXINT(PB0_A0_CMU_00, _BIT6) == _BIT6) // MHL Mode
    {
        // Disable All Adaptation Loop
        ScalerSetBit_EXINT(P7A_AC_L0_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_BC_L1_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetBit_EXINT(P7A_CC_L2_DFE_EN_3, ~(_BIT1 | _BIT0), 0x00);
        ScalerSetByte_EXINT(P7A_A1_L0_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_B1_L1_DFE_EN_2, 0x00);
        ScalerSetByte_EXINT(P7A_C1_L2_DFE_EN_2, 0x00);

        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);
    }
    else
#endif
    {
        // Disable the Vth Adaptation Loop
        ScalerSetBit_EXINT(P7A_A1_L0_DFE_EN_2, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7A_B1_L1_DFE_EN_2, ~_BIT6, 0x00);
        ScalerSetBit_EXINT(P7A_C1_L2_DFE_EN_2, ~_BIT6, 0x00);
    }

    // [0] en_data_manual = 1 --> Enable Dataout
    ScalerSetBit_EXINT(PB0_F7_DATA_TIMER, ~_BIT0, _BIT0);

    if(GET_D1_INPUT_PIXEL_CLK() > 3400) // 3400~6000 Hybrid CDR
    {
        // [0] en_eqen_manual = 0 --> Disable Adaptation
        ScalerSetBit_EXINT(PB0_F6_EQEN_TIMER, ~_BIT0, 0x00);

        // [5] reg_adp_eq_off = 1'b1 --> Disable Adaptation for Analog CDR
        ScalerSetBit_EXINT(PB0_F9_LANE0_A_CDR_03, ~_BIT5, _BIT5);

        // [4] reg_en_data_manual_l0 = 1'b1
        // [3] reg_bypass_data_rdy_l0 = 1'b1
        ScalerSetBit_EXINT(PB0_FF_LANE0_A_CDR_09, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));
    }

    // Enable Sumamp High Gain Mode
    ScalerSetBit_EXINT(PB0_B0_CDR_07, ~_BIT1, _BIT1);

    // Reset PHY -> MAC Interface
    ScalerSetBit_EXINT(P70_A7_TMDS_PWDCTL, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit_EXINT(P70_A7_TMDS_PWDCTL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Reset HDMI 3 Channel FIFO
    ScalerSetBit_EXINT(P70_B0_TMDS_CHANNEL_FIFO, ~_BIT6, _BIT6);

    // HDMI 3 Channel FIFO Global Enable
    ScalerSetBit_EXINT(P70_B0_TMDS_CHANNEL_FIFO, ~(_BIT7 | _BIT6), _BIT7);

    // Clear RGB Data Detection Flags
    ScalerSetBit_EXINT(P70_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5));
}

//--------------------------------------------------
// Description  : TMDS Interrupt Process (EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1IntHandler_EXINT0(void) using 1
{
#if(_D1_HDMI_2_0_SUPPORT == _ON)
    BYTE pucBackUp[4];
#else
    BYTE pucBackUp[2];
#endif

    WORD usCount = 0;

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    bit bMHLFail = _FALSE;
#endif

    pucBackUp[0] = ScalerGetByte_EXINT(P70_C9_HDMI_AP);
    pucBackUp[1] = ScalerGetByte_EXINT(P70_C8_HDMI_APC);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
    pucBackUp[2] = ScalerGetByte_EXINT(P70_39_HDMI_CTRL_39);
    pucBackUp[3] = ScalerGetByte_EXINT(P70_38_HDMI_CTRL_38);
#endif

    // Freq. Stable Into IRQ
    if((ScalerGetByte_EXINT(P70_EF_HDMI_ERROR_TH) & 0xC0) == 0xC0)
    {
        // Disable Freq Stable IRQ
        ScalerSetBit_EXINT(P70_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), _BIT6);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        // Set SCDC Port Clock Detected
        ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
        ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

        // Disable Reset HDMI/DVI Format
        ScalerSetBit_EXINT(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_10_PORT_PAGE70_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P70_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
#endif

        // Enable Freq unstable IRQ
        ScalerSetBit_EXINT(P70_E6_HDMI_FREQDET_CTRL, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

        // Pop up Counter Value
        ScalerSetBit_EXINT(P70_EC_HDMI_FREQDET_STABLE, ~_BIT7, _BIT7);

        usCount = (WORD)(((ScalerGetByte_EXINT(P70_ED_HDMI_FREQDET_RESULT_M) & 0x7F) << 8) | ScalerGetByte_EXINT(P70_EE_HDMI_FREQDET_RESULT_L));

        // TMDS_FREQ(MHz) = GDI_CLK(MHz) * CLK_COUNT * _TMDS_MEASURE_CLOCK_DIVIDER / _TMDS_MEASURE_CLOCK_COUNTER
        SET_D1_INPUT_PIXEL_CLK((((DWORD)_GDI_CLK_KHZ * usCount + 50000) / 100000));

#if(_D1_HDMI_2_0_SUPPORT == _ON)

        // If SCDC tell 1:40 then set High speed flag
        if((GET_D1_INPUT_PIXEL_CLK() >= 850) && (GET_D1_INPUT_PIXEL_CLK() <= 1500))
        {
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_20_PORT_PAGE70_HDMI_SCDC_20);

            if(ScalerGetBit_EXINT(P70_3A_HDMI_CTRL_3A, _BIT1) == _BIT1)
            {
                SET_TMDS_RX1_HIGH_SPEED_MODE();
            }
        }

        if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
        {
            SET_D1_INPUT_PIXEL_CLK((GET_D1_INPUT_PIXEL_CLK() * 4));
        }
#endif

        if((GET_TMDS_RX1_PHY_SET() == _FALSE) || ((bit)ScalerTMDSRx1CheckCDRStable_EXINT0(g_usTMDSRx1ClkCount) == _FALSE))
        {
            g_usTMDSRx1ClkCount = ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS);

            // TMDS_OFFLine Measure FREQ(MHz) = GDI_CLK(MHz) * 1024 / g_usTMDSRx1ClkCount
            SET_TMDS_D1_OFFLINE_MEASURE_CLK(((DWORD)(_GDI_CLK_KHZ * 1024) / 100) / g_usTMDSRx1ClkCount);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
            {
                SET_TMDS_D1_OFFLINE_MEASURE_CLK((GET_TMDS_D1_OFFLINE_MEASURE_CLK() * 4));
            }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR);

#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
                // Set HDMI/DVI switch to Auto Mode
                ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
#else
                // Set HDMI/DVI switch to Manual Mode and Forced to HDMI
                ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif
                SET_TMDS_RX1_CLK_MODE(_TMDS_MHL_PPMODE_PHY_SETTING);

                SET_D1_INPUT_PIXEL_CLK(GET_D1_INPUT_PIXEL_CLK() * 4);
                ScalerTMDSRx1SetPhy_EXINT0();
                SET_D1_INPUT_PIXEL_CLK(GET_D1_INPUT_PIXEL_CLK() / 4);

                // Enable Packed Pixel Mode
                ScalerSetBit_EXINT(P75_A0_MHL_CTRL_00, ~_BIT1, _BIT1);

                // Check CDR Stable
                if((ScalerTMDSRx1CheckCDRStable_EXINT0(g_usTMDSRx1ClkCount) == _FALSE) || (ScalerMHLRx1DetectClkMode_EXINT0() == _FALSE))// MHL mode need modify
                {
                    SET_TMDS_RX1_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                    // TMDS_FREQ(MHz) = GDI_CLK(MHz) * 1024 / CLK_COUNT = GDI_CLK(KHz) * 1024 / (CLK_COUNT * 1024)
                    SET_D1_INPUT_PIXEL_CLK(GET_D1_INPUT_PIXEL_CLK() * 3);
                    ScalerTMDSRx1SetPhy_EXINT0();
                    SET_D1_INPUT_PIXEL_CLK(GET_D1_INPUT_PIXEL_CLK() / 3);

                    // Disable Packed Pixel Mode
                    ScalerSetBit_EXINT(P75_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                    if((ScalerTMDSRx1CheckCDRStable_EXINT0(g_usTMDSRx1ClkCount) == _FALSE) || (ScalerMHLRx1DetectClkMode_EXINT0() == _FALSE))// MHL Need modify
                    {
                        bMHLFail = _TRUE;
                    }
                }
            }
            else
            {
                SET_TMDS_RX1_CLK_MODE(_TMDS_24BIT_PHY_SETTING);

                ScalerTMDSRx1SetPhy_EXINT0();

                // Disable Packed Pixel Mode
                ScalerSetBit_EXINT(P75_A0_MHL_CTRL_00, ~_BIT1, 0x00);

                // Set HDMI/DVI switch to Auto Mode
                ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR);
                ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);
            }
#else
            ScalerTMDSRx1SetPhy_EXINT0();
#endif
        }

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        if(bMHLFail == _FALSE)
#endif
        {
            // Set Upper Bound (allow 1/64 freq shift)
            ScalerSetByte_EXINT(P70_E8_HDMI_FREQDET_UPPER_M, (HIBYTE(usCount + (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(usCount + (usCount >> 6)));

            // Set Lower Bound
            ScalerSetByte_EXINT(P70_EA_HDMI_FREQDET_LOWER_M, (HIBYTE(usCount - (usCount >> 6)) & 0x7F));
            ScalerSetByte_EXINT(P70_EB_HDMI_FREQDET_LOWER_L, LOBYTE(usCount - (usCount >> 6)));

            // Release Key Calculation
            ScalerSetBit_EXINT(P70_AE_TMDS_RPS, ~_BIT1, _BIT1);

            // Reset Color Depth to 8 Bits
            SET_COLOR_DEPTH(_D1_INPUT_PORT, _COLOR_DEPTH_8_BITS);

            SET_TMDS_RX1_PHY_SET();
        }
    }

    // Freq. Unstable Into IRQ
    if((ScalerGetByte_EXINT(P70_E6_HDMI_FREQDET_CTRL) & 0x06) == 0x06)
    {
        // Clear Unstable IRQ Flag
        ScalerSetBit_EXINT(P70_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

        // Ensure Freq really unstable
        if((abs(g_usTMDSRx1ClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (g_usTMDSRx1ClkCount >> 6)) ||
           (abs(GET_D1_INPUT_PIXEL_CLK() - ((GET_TMDS_D1_OFFLINE_MEASURE_CLK() << 3) / ((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) ? _COLOR_DEPTH_8_BITS : GET_COLOR_DEPTH(_D1_INPUT_PORT)))) > (GET_D1_INPUT_PIXEL_CLK() >> 6)))
        {
            if((GET_TMDS_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M1) != 0)
            {
                // Set Display M1 output force to background color and free run mode
                ScalerSetBit_EXINT(P0_28_VIDEO_DISPLAY_CONTROL_REG, ~_BIT5, _BIT5);
            }

            if((GET_TMDS_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_M2) != 0)
            {
                // Set Display M2 output force to background color and free run mode
                ScalerSetBit_EXINT(P40_28_VIDEO_DISPLAY_CONTROL_REG_M2, ~_BIT5, _BIT5);
            }

            if((GET_TMDS_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S1) != 0)
            {
                // Set Display S1 output force to background color and free run mode
                ScalerSetBit_EXINT(P80_28_VIDEO_DISPLAY_CONTROL_REG_S1, ~_BIT5, _BIT5);
            }

            if((GET_TMDS_RX1_FORCE_BCKGRD_PATH() & _DISPLAY_PATH_S2) != 0)
            {
                // Set Display S2 output force to background color and free run mode
                ScalerSetBit_EXINT(PC0_28_VIDEO_DISPLAY_CONTROL_REG_S2, ~_BIT5, _BIT5);
            }

            // Disable RGB/clock Output to avoid garbage
            ScalerSetBit_EXINT(P70_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), 0x00);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            // Clear Scrambling Detection Flag
            ScalerSetBit_EXINT(P70_01_HDMI_CTRL_01, ~_BIT3, _BIT3);

            // Disable Scrambling Status
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_21_PORT_PAGE70_HDMI_SCDC_21);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, 0x00);

            // Disable CED Function
            ScalerSetBit_EXINT(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Pop Up CED Error For Clear Error Counter
            ScalerSetBit_EXINT(P70_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

            // Disable CED Lock Transition IRQ & Flag
            ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit_EXINT(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Update Flag & CED Update Flag
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_10_PORT_PAGE70_HDMI_SCDC_10);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~(_BIT1 | _BIT0), 0x00);

            // Clear SCDC Port Status Lock Flag
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Reset HDMI/DVI Format
            ScalerSetBit_EXINT(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
#endif
            // Disable Freq. Unstable IRQ
            ScalerSetBit_EXINT(P70_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Set HDMI/DVI switch to Auto Mode
            ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR);
            ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~(_BIT7 | _BIT6 | _BIT3), 0x00);

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte_EXINT(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte_EXINT(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));

                // Suspend Key Calculation before load key
                ScalerSetBit_EXINT(P70_AE_TMDS_RPS, ~_BIT1, 0x00);
            }
            else
#endif
            {
                // Set Upper Bound
                ScalerSetByte_EXINT(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte_EXINT(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            }

            // Set Lower Bound
            ScalerSetByte_EXINT(P70_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte_EXINT(P70_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit_EXINT(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit_EXINT(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit_EXINT(P70_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            CLR_TMDS_RX1_PHY_SET();

#if(_D1_HDMI_2_0_SUPPORT == _ON)
            CLR_TMDS_RX1_HIGH_SPEED_MODE();
#endif
        }
    }

#if(_D1_HDMI_2_0_SUPPORT == _ON)

    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P70_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P70_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P70_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX1_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P70_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Detect CED Channel 2 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT2) == _BIT2) && (ScalerGetBit_EXINT(P70_18_HDMI_CTRL_18, _BIT2) == _BIT2))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT2);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT5) == _BIT5)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT3, _BIT3);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT3, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_10_PORT_PAGE70_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P70_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 1 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT1) == _BIT1) && (ScalerGetBit_EXINT(P70_18_HDMI_CTRL_18, _BIT1) == _BIT1))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT1);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT4) == _BIT4)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT2, _BIT2);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT2, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_10_PORT_PAGE70_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P70_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Detect CED Channel 0 Lock Transition Flag into IRQ
    if((ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT0) == _BIT0) && (ScalerGetBit_EXINT(P70_18_HDMI_CTRL_18, _BIT0) == _BIT0))
    {
        // Clear Lock Transition Flag
        ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), _BIT0);

        // Detect CED Realtime Flag
        if(ScalerGetBit_EXINT(P70_17_HDMI_CTRL_17, _BIT3) == _BIT3)
        {
            // Set CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT1, _BIT1);
        }
        else
        {
            // Clear CED Lock Flag in SCDC Port
            ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_40_PORT_PAGE70_HDMI_SCDC_40);
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT1, 0x00);
        }

        // Set SCDC Port Status Update Flag
        ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, _P70_3A_PT_10_PORT_PAGE70_HDMI_SCDC_10);

        if(ScalerGetBit_EXINT(P70_3A_HDMI_CTRL_3A, _BIT0) == 0x00)
        {
            ScalerSetBit_EXINT(P70_3A_HDMI_CTRL_3A, ~_BIT0, _BIT0);

            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);

                // Enable Read Request Done IRQ
                ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
            }
        }
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P70_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P70_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSRx1ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P70_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
    if(ScalerGetBit_EXINT(P70_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P70_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P70_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX1_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P70_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSRx1CheckCDRStable_EXINT(g_usTMDSRx1ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P70_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }

#endif // End of #if(_D1_HDMI_2_0_SUPPORT == _ON)

    // Clear IRQ Pending Flag
    ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_60_PORT_PAGE70_HDMI_INTCR);
    ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~_BIT7, _BIT7);

    ScalerSetByte_EXINT(P70_C8_HDMI_APC, pucBackUp[1]);
    ScalerSetByte_EXINT(P70_C9_HDMI_AP, pucBackUp[0]);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
    ScalerSetByte_EXINT(P70_38_HDMI_CTRL_38, pucBackUp[3]);
    ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, pucBackUp[2]);
#endif
}

//--------------------------------------------------
// Description  : Check CDR Locked
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
bit ScalerTMDSRx1CheckCDRStable(WORD usClkCount)
{
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX1_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    DebugMessageRx1("R Channel CDR Unstable", ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    DebugMessageRx1("R Channel CDR Unstable", ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED));
                    return _FALSE;
                }

                break;

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif
    {
#if(_D1_HDMI_2_0_SUPPORT == _ON)

        if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx1MeasureClk(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx1MeasureClk(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx1MeasureClk(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Check CDR Locked (EXINT0 Only)
// Input Value  : Measured Clk Count to be compared
// Output Value : _TRUE => Stable
//--------------------------------------------------
BYTE ScalerTMDSRx1CheckCDRStable_EXINT0(WORD usClkCount) using 1
{
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        switch(GET_TMDS_RX1_CLK_MODE())
        {
            // Check if Packed Pixel Mode
            case _TMDS_MHL_PPMODE_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            // Check if 24 Bit Mode
            case _TMDS_24BIT_PHY_SETTING:

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                // Check Current Measured Freq. is the same as previously locked
                if(abs(usClkCount - (ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_RED) * 3)) > (usClkCount >> 6))
                {
                    return _FALSE;
                }

                break;

            default:

                return _FALSE;
                break;
        }
    }
    else
#endif
    {
#if(_D1_HDMI_2_0_SUPPORT == _ON)

        if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_RED) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_BLUE) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }

            if(abs(usClkCount - (ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_GREEN) * 4)) > (usClkCount >> 5))
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            // Check Current Measured Freq. is the same as previously locked
            if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_TMDS)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_RED)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_BLUE)) > (usClkCount >> 6))
            {
                return _FALSE;
            }

            if(abs(usClkCount - ScalerTMDSRx1MeasureClk_EXINT0(_CLK_SOURCE_GREEN)) > (usClkCount >> 6))
            {
                return _FALSE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Measure Clk
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSRx1MeasureClk(BYTE ucMeasureClk)
{
    BYTE ucDelayCount = 0;

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte(PB0_A1_CMU_01, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte(PB0_A1_CMU_01, 0xF7);
    }

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit(P70_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    // Start Measure
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_28_PORT_PAGE70_HDMI_NTX1024TR0, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        Delay5us(g_ucDelay5usN);

        if((ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_28_PORT_PAGE70_HDMI_NTX1024TR0, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerGetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_28_PORT_PAGE70_HDMI_NTX1024TR0, 2, &pData[0], _AUTOINC);

    return ((WORD)(pData[0] & 0x07) << 8) | pData[1];
}

//--------------------------------------------------
// Description  : Measure Clk (EXINT0 Only)
// Input Value  : Clk Source to be measured
// Output Value : Measured Clk Count
//--------------------------------------------------
WORD ScalerTMDSRx1MeasureClk_EXINT0(BYTE ucMeasureClk) using 1
{
    BYTE ucDelayCount = 0;
    WORD usClkCount = 0;
    BYTE ucBackUp = 0;

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Enable CMU_EN(Lane0) and Rx_EN(Lane0,3)
        ScalerSetByte_EXINT(PB0_A1_CMU_01, 0x91);
    }
    else
#endif
    {
        // Enable CMU_EN(Lane0,1,2) and Rx_EN(Lane0,1,2,3)
        ScalerSetByte_EXINT(PB0_A1_CMU_01, 0xF7);
    }

    // Select reference clk to Xtal Clk and measure clk
    ScalerSetBit_EXINT(P70_AD_TMDS_CPS, ~(_BIT6 | _BIT5 | _BIT4), ((ucMeasureClk << 5) | _BIT4));

    ucBackUp = ScalerGetByte_EXINT(P70_C8_HDMI_APC);

    // Start Measure
    ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_28_PORT_PAGE70_HDMI_NTX1024TR0);
    ScalerSetBit_EXINT(P70_CA_HDMI_DP, ~_BIT3, _BIT3);

    // Delay at least 40us at Xtal = 27MHz
    for(ucDelayCount = 0; ucDelayCount <= 8; ucDelayCount++)
    {
        Delay5us(g_ucDelay5usN);

        if((ScalerGetBit_EXINT(P70_CA_HDMI_DP, _BIT3)) == 0x00)
        {
            break;
        }
    }

    ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_28_PORT_PAGE70_HDMI_NTX1024TR0);
    usClkCount = ((WORD)(ScalerGetByte_EXINT(P70_CA_HDMI_DP) & 0x07) << 8);

    ScalerSetByte_EXINT(P70_C9_HDMI_AP, _P70_CA_PT_29_PORT_PAGE70_HDMI_NTX1024TR1);
    usClkCount =  usClkCount | ScalerGetByte_EXINT(P70_CA_HDMI_DP);

    ScalerSetByte_EXINT(P70_C8_HDMI_APC, ucBackUp);

    return usClkCount;
}

//--------------------------------------------------
// Description  : TMDS Video Setting
// Input Value  : Source Type
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1DviVideoSetting(void)
{
    // Manual Set Color Space and disable pixel repetition
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Disable Down Sampling
    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_50_PORT_PAGE70_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Waiting for Down Sampling Effect
    ScalerTimerDelayXms(20);

    SET_COLOR_SPACE(_D1_INPUT_PORT, _COLOR_SPACE_RGB);
    SET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT, _RGB_QUANTIZATION_FULL_RANGE);

    ScalerTMDSRx1SetPorchColor(GET_COLOR_SPACE(_D1_INPUT_PORT));
}

//--------------------------------------------------
// Description  : Set Back Ground Color
// Input Value  : Current Color Space
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1SetPorchColor(EnumColorSpace enumColorFormat)
{
    // Manual Set Background Color Enable
    ScalerSetBit(P70_B9_TMDS_OUT_CTRL, ~_BIT7, 0x00);

    if((enumColorFormat == _COLOR_SPACE_YCBCR444) || (enumColorFormat == _COLOR_SPACE_YCBCR422))
    {
        ScalerSetByte(P70_BA_TMDS_ROUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P70_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P70_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P70_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
    else if(enumColorFormat == _COLOR_SPACE_YCBCR420)
    {
        ScalerSetByte(P70_BA_TMDS_ROUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P70_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BC_TMDS_GOUT_HIGH_BYTE, 0x10);
        ScalerSetByte(P70_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BE_TMDS_BOUT_HIGH_BYTE, 0x80);
        ScalerSetByte(P70_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
#endif
    else
    {
        ScalerSetByte(P70_BA_TMDS_ROUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P70_BB_TMDS_ROUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BC_TMDS_GOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P70_BD_TMDS_GOUT_LOW_BYTE, 0x00);
        ScalerSetByte(P70_BE_TMDS_BOUT_HIGH_BYTE, 0x00);
        ScalerSetByte(P70_BF_TMDS_BOUT_LOW_BYTE, 0x00);
    }
}

#if(_D1_HDMI_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Deep Color Proc
// Input Value  : void
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerTMDSRx1HdmiDeepColorProc(WORD usTmdsClkCnt)
{
    // Setting Deep Color PLL
    if(ScalerTMDSRx1HdmiSetDeepColorPll(usTmdsClkCnt, GET_COLOR_DEPTH(_D1_INPUT_PORT)) == _FALSE)
    {
        return _FALSE;
    }

    // Wait for Phase lock
    if(ScalerTMDSRx1HdmiWaitDeepColorPllLock() == _FALSE)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Set Deep Color PLL
// Input Value  : usTMDSClkCount, ucColorDepth
// Output Value : None
//--------------------------------------------------
bit ScalerTMDSRx1HdmiSetDeepColorPll(WORD usTMDSClkCount, BYTE ucColorDepth)
{
    DWORD ulTMDSClkValue = 0;
    WORD usM = 0;
    BYTE ucN = 0;
    BYTE ucDivS = 0;
    BYTE ucFactor = 0;

#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_HDMI_2_0_YCBCR420_SUPPORT == _ON))
    BYTE ucRatio = 1;
#endif

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

#if(_D1_HDMI_2_0_SUPPORT == _ON)

    if(GET_TMDS_RX1_HIGH_SPEED_MODE() == _TRUE)
    {
        ulTMDSClkValue = (ulTMDSClkValue << 2);
    }

#if(_HDMI_2_0_YCBCR420_SUPPORT == _ON)
    if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
    {
        ucRatio = 2;
    }
#endif

#endif

    DebugMessageRx1("TMDS clk", ulTMDSClkValue);
    DebugMessageRx1("Color Depth", ucColorDepth);

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
#if((_D1_HDMI_2_0_SUPPORT == _ON) && (_HDMI_2_0_YCBCR420_SUPPORT == _ON))
            usM = (WORD)ucN * ((pData[15] == 0) ? 1 : pData[15]) * (ucFactor - 1) / ucFactor * ucRatio;
#else
            usM = (WORD)ucN * ((pData[15] == 0) ? 1 : pData[15]) * (ucFactor - 1) / ucFactor;
#endif

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
            DebugMessageRx1("4. PLL Setting Error", 0);
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
    ScalerSetBit(PB8_BE_MN_SCLKG_PLL_CHP, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

    // BW = Kvco * Icp * R / (M * 2pi) = 700k --> Icp = M * BW * 2pi / Kvco / R
    PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / _PLL_VCO_BAND_10 / ((7 + (ScalerGetBit(PB8_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);
    pData[5] = (PDATA_WORD(1) + 25) / 50;
    pData[5] -= ((pData[5] == 0) ? 0 : 1);

    if(pData[5] > 0x07)
    {
        pData[5] = 0x07;
    }

    DebugMessageRx1("Deep Color Charge Pump icp =", pData[5]);

    // DPPLL Power Down
    ScalerSetByte(PB8_BD_MN_SCLKG_PLL_PWR, 0x80);

    // Disable M/N Tracking
    ScalerSetBit(PB8_A7_MN_SCLKG_TRK_CTRL, ~(_BIT7 | _BIT6 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

    // Set PLL Charge Pump Current
    ScalerSetBit(PB8_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

    // Set VCOMD, phase Swallow Circuit Clock Select, SCLKGSTOP
    ScalerSetBit(PB8_BF_MN_SCLKG_PLL_WD, ~(0x7F), 0x16);

    // Set DPPLL Div_2 & Div_s
    ScalerSetByte(PB8_A3_MN_SCLKG_DIVS, (ucDivS >> 1));

    // Set DPPLL Div_O.
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~(_BIT1 | _BIT0), (0 & (_BIT1 | _BIT0)));

    // Offset Value Setting
    ScalerSetByte(PB8_A6_MN_SCLKG_OFFS_L, 0);
    ScalerSetByte(PB8_A5_MN_SCLKG_OFFS_M, 0);
    ScalerSetBit(PB8_A4_MN_SCLKG_OFFS_H, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PB8_A7_MN_SCLKG_TRK_CTRL, ~(_BIT1 | _BIT0), 0x00);

    // Enable phase swallow
    ScalerSetBit(PB8_B8_MN_SCLKG_SDM_CTRL, ~(_BIT5 | _BIT4), _BIT4);

    // Set DPPLL M Code
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~(_BIT1 | _BIT0), (HIBYTE(usM - 2) & 0x03));
    ScalerSetByte(PB8_A1_MN_SCLKG_DIVM, LOBYTE(usM - 2));

    // Set DPPLL N Code
    ScalerSetByte(PB8_A2_MN_SCLKG_DIVN, (ucN - 2));

    // PLL Input Clock select to Link Clock, Output Clock Select to PLL Clock, Double Buffer.
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT4));

    // Load offset value
    ScalerSetBit(PB8_A4_MN_SCLKG_OFFS_H, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7);

    // Double Buffer for M/N Tracking
    ScalerSetBit(PB8_A0_MN_SCLKG_CTRL, ~_BIT4, _BIT4);

    // DPLL VCORSTB Set to Normal
    ScalerSetBit(PB8_C0_MN_SCLKG_PLL_INSEL, ~_BIT0, _DPLL_VCORSTB_NORMAL_VALUE);

    // DPLL Power On
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT7, 0x00);

    ScalerTimerDelayXms(2);

    ////////////////////////////////
    // DPPLL VCO Band Calibration //
    ////////////////////////////////

    // Reg DPLL_CMPEN
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT2, _BIT2);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALLCH
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT3, _BIT3);

    ScalerTimerDelayXms(2);

    // Reg DPLL_CALSW
    ScalerSetBit(PB8_BD_MN_SCLKG_PLL_PWR, ~_BIT4, _BIT4);

    // Check VCO Band is '10
    if(ScalerGetBit(PB8_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) != _BIT5)
    {
        switch(ScalerGetBit(PB8_C0_MN_SCLKG_PLL_INSEL, (_BIT5 | _BIT4)) >> 4)
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

        PDATA_WORD(1) = ((DWORD)usM * 700UL * 2 * 314UL * 20) / PDATA_WORD(0) / ((7 + (ScalerGetBit(PB8_BE_MN_SCLKG_PLL_CHP, (_BIT7 | _BIT6 | _BIT5)) >> 5) * 2) * 100);

        DebugMessageRx1("4. reset Icp", PDATA_WORD(1));

        pData[5] = (PDATA_WORD(1) + 25) / 50;
        pData[5] -= ((pData[5] == 0) ? 0 : 1);

        if(pData[5] > 0x07)
        {
            pData[5] = 0x07;
        }

        // Set PLL Charge Pump Current
        ScalerSetBit(PB8_BE_MN_SCLKG_PLL_CHP, ~(_BIT2 | _BIT1 | _BIT0), (pData[5] & 0x07));

        DebugMessageRx1("4. VCO is not band10, reset Icp", pData[5]);
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Wait for Deep Color PLL Phase Lock
// Input Value  : None
// Output Value : _TRUE = > Phase Locked
//--------------------------------------------------
bit ScalerTMDSRx1HdmiWaitDeepColorPllLock(void)
{
    BYTE ucTemp = 0;

    do
    {
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_82_PORT_PAGE70_HDMI_DPC_SET2, ~(_BIT4 | _BIT3), (_BIT4 | _BIT3));

        // Delay for PLL Phase Lock
        ScalerTimerDelayXms(2);

        ucTemp++;
    }
    while((ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_82_PORT_PAGE70_HDMI_DPC_SET2, _BIT1) != 0) && (ucTemp <= 15));

    if(ucTemp > 15)
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Detect HDMI Info Frame
// Input Value  : bWait => Whether to wait then read
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HdmiPacketDetect(bit bWait)
{
    if(bWait == _WAIT)
    {
        // Polling 3 frame for detect Packet signals
        if(ScalerTimerPollingFlagProc(130, P70_CC_HDMI_GPVS, (_BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // Both GCP & AVI infoframe packet have been received
            if(ScalerGetBit(P70_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == (_BIT6 | _BIT5))
            {
                SET_HDMI_RX1_GCP_RECEIVED();

                SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
            }
            // Only AVI infoframe packet have been received
            else if(ScalerGetBit(P70_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT5)
            {
                SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();

                // Polling more 1 frame to wait GCP packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P70_CC_HDMI_GPVS, _BIT6, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX1_GCP_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX1_GCP_RECEIVED();
                }
            }
            // Only GCP Packet have been received
            else if(ScalerGetBit(P70_CC_HDMI_GPVS, (_BIT6 | _BIT5)) == _BIT6)
            {
                SET_HDMI_RX1_GCP_RECEIVED();

                // Polling more 1 frame to wait AVI infoframe packet for HW can't update bit 6 & bit 5 simultaneously
                if(ScalerTimerPollingFlagProc(45, P70_CC_HDMI_GPVS, _BIT5, _TRUE) == _TRUE)
                {
                    SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
                }
                else
                {
                    CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
                }
            }
        }
        // Neither AVI infoframe nor GCP packet received
        else
        {
            CLR_HDMI_RX1_GCP_RECEIVED();

            CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        // Polling 3 frame for detect Packet signals P70_CA_00[7]
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerTimerPollingDataBitFlagProc(130, P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, _BIT7, _TRUE) == _TRUE))
#else
        // Polling 3 frame for detect Packet signals P70_CA_00[7]
        if(ScalerTimerPollingDataBitFlagProc(130, P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, _BIT7, _TRUE) == _TRUE)
#endif
        {
            SET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX1_SPD_INFO_FRAME_RECEIVED();
        }
#endif
        // Wait at least 3 frame for HW auto update color depth value
        ScalerTimerDelayXms(130);

        CLR_HDMI_RX1_PACKET_DETECTING();
    }
    else
    {
        if(ScalerGetBit(P70_CC_HDMI_GPVS, _BIT6) == _BIT6)
        {
            ScalerTMDSRx1HdmiWatchDog(_HDMI_AV_MUTE_WD, _ENABLE);

            SET_HDMI_RX1_GCP_RECEIVED();
        }
        else
        {
            ScalerTMDSRx1HdmiWatchDog(_HDMI_AV_MUTE_WD, _DISABLE);

            CLR_HDMI_RX1_GCP_RECEIVED();
        }

        if(ScalerGetBit(P70_CC_HDMI_GPVS, _BIT5) == _BIT5)
        {
            // Color Space Auto/ Pixel Repetition auto mode
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT2), (_BIT6 | _BIT2));

            ScalerTMDSRx1HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _ENABLE);

            SET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
        }
        else
        {
            // Mannal Set Color Space and disable pixel  repetition
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_51_PORT_PAGE70_HDMI_ACRCR, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

            // Disable down sampling
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_50_PORT_PAGE70_HDMI_VCR, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            // Waiting for Down Sampling Effect
            ScalerTimerDelayXms(20);

            ScalerTMDSRx1HdmiWatchDog(_HDMI_AVI_INFO_VARIATION_WD, _DISABLE);

            CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE)
        if((GET_HDMI_FREESYNC_VCP() == 0x01) && (ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, _BIT7) == _BIT7))
#else
        if(ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, _BIT7) == _BIT7)
#endif
        {
            SET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED();
        }
        else
        {
            CLR_TMDS_RX1_SPD_INFO_FRAME_RECEIVED();
        }
#endif

        // Clear Detection Flag
        ScalerSetBit(P70_CC_HDMI_GPVS, ~_BIT6, _BIT6);

        ScalerSetBit(P70_CC_HDMI_GPVS, ~_BIT5, _BIT5);

        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);

        SET_HDMI_RX1_PACKET_DETECTING();

        // Activate Packet Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.13), _SCALER_TIMER_EVENT_RX1_TMDS_HDMI_PACKET_DETECT);
    }
}

//--------------------------------------------------
// Description  : HDMI Info Frame Packet Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HdmiPacketDetectEvent(void)
{
    CLR_HDMI_RX1_PACKET_DETECTING();
}

//--------------------------------------------------
// Description  : Get HDMI AVI Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx1HdmiGetAVIInfo(EnumAviInfoContent enumContent)
{
    if(GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED() == _TRUE)
    {
        switch(enumContent)
        {
            case _AVI_INFO_COLOR_SPACE:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x04, (_BIT6 | _BIT5)) >> 5);

            case _AVI_INFO_COLORIMETRY:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x05, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_EXTENDED_COLORIMETRY:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x06, (_BIT6 | _BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_RGB_QUANTIZATION:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x06, (_BIT3 | _BIT2)) >> 2);

            case _AVI_INFO_YCC_QUANTIZATION:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x08, (_BIT7 | _BIT6)) >> 6);

            case _AVI_INFO_SCAN_INFO:

                return ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x04, (_BIT1 | _BIT0));

            case _AVI_INFO_IT_CONTENT:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x06, _BIT7) >> 7);

            case _AVI_INFO_PIXEL_REPETITION:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x08, (_BIT3 | _BIT2 | _BIT1 | _BIT0)));

            case _AVI_INFO_AR:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x05, (_BIT5 | _BIT4)) >> 4);

            case _AVI_INFO_VIC:

                return (ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x07, (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0)));

            default:

                break;
        }
    }

    return 0xFF;
}

//--------------------------------------------------
// Description  : Detect HDMI AVI pixel repetition
// Input Value  : None
// Output Value : _TRUE => Current Info is different from previous setting
//--------------------------------------------------
bit ScalerTMDSRx1HdmiAviPixelRepInfoChanged(void)
{
    // Check Tmds Pixel Repetition
    if(ScalerTMDSRx1HdmiGetAVIInfo(_AVI_INFO_PIXEL_REPETITION) != GET_TMDS_RX1_AVI_PIXEL_REPETITION())
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get Color Depth
// Input Value  : None
// Output Value : Received Color Depth
//--------------------------------------------------
BYTE ScalerTMDSRx1HdmiGetColorDepth(void)
{
    if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422)
    {
        return _COLOR_DEPTH_12_BITS;
    }

    if(GET_HDMI_RX1_GCP_RECEIVED() == _TRUE)
    {
        if(ScalerGetBit(P70_B4_TMDS_DPC0, 0x07) == 0x05)
        {
            return _COLOR_DEPTH_10_BITS;
        }
        else if(ScalerGetBit(P70_B4_TMDS_DPC0, 0x07) == 0x06)
        {
            return _COLOR_DEPTH_12_BITS;
        }
        else if(ScalerGetBit(P70_B4_TMDS_DPC0, 0x07) == 0x07)
        {
            return _COLOR_DEPTH_16_BITS;
        }
    }

    return _COLOR_DEPTH_8_BITS;
}

//--------------------------------------------------
// Description  : Hdmi Handle AVMute Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HdmiAVMuteProc(void)
{
    // if AVMute Has been triggered
    if((ScalerGetBit(P70_CB_HDMI_SR, _BIT6) == 0x00) && (ScalerGetBit(P70_A6_TMDS_OUTCTL, (_BIT6 | _BIT5 | _BIT4)) == 0x00))
    {
        // Clear AVMute Flag
        ScalerSetBit(P70_CB_HDMI_SR, ~_BIT7, _BIT7);

        // Disable AVMute Watch Dog
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_31_PORT_PAGE70_HDMI_WDCR0, ~_BIT7, 0x00);

        // Enable Video/Audio Output
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_30_PORT_PAGE70_HDMI_AVMCR, ~(_BIT5 | _BIT3), (_BIT5 | _BIT3));

        // Enable RGB Output
        ScalerSetBit(P70_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

        // Enable AVMute Watch Dog
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_31_PORT_PAGE70_HDMI_WDCR0, ~_BIT7, _BIT7);
    }
}

//--------------------------------------------------
// Description  : Hdmi Enable Watch Dog
// Input Value  : ucWDType => Watch Dog type, bEnable => Enable watch dog flag
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HdmiWatchDog(BYTE ucWDType, bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            if(ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_41_PORT_PAGE70_HDMI_VWDSR, _BIT0) == 0x00)
            {
                // Clear AVI Info Frame Variation flag
                ScalerSetBit(P70_CC_HDMI_GPVS, ~(_BIT6 | _BIT5 | _BIT0), _BIT0);

                if((GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR444) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR422) || (GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420))
                {
                    // Enable Color Space/ Colorimetry Change Detection
                    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_45_PORT_PAGE70_HDMI_PVGCR0, ~(_BIT3 | _BIT0), (_BIT3 | _BIT0));
                }
                else
                {
                    // Enable Color Space Change Detection
                    ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_45_PORT_PAGE70_HDMI_PVGCR0, ~(_BIT3 | _BIT0), _BIT0);
                }

                // Enable AVI Info Frame Variation Watch Dog
                ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_41_PORT_PAGE70_HDMI_VWDSR, ~_BIT0, _BIT0);
            }
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            if(ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_31_PORT_PAGE70_HDMI_WDCR0, _BIT7) == 0x00)
            {
                // CLR AVMute Flag
                ScalerSetBit(P70_CB_HDMI_SR, ~_BIT7, _BIT7);

                // Enable AVMute WD
                ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_31_PORT_PAGE70_HDMI_WDCR0, ~_BIT7, _BIT7);
            }
        }
    }
    else
    {
        if((ucWDType & _HDMI_AVI_INFO_VARIATION_WD) == _HDMI_AVI_INFO_VARIATION_WD)
        {
            // Disable packet variation Watch Dog
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_41_PORT_PAGE70_HDMI_VWDSR, ~_BIT0, 0x00);

            ScalerSetDataPortByte(P70_C9_HDMI_AP, _P70_CA_PT_45_PORT_PAGE70_HDMI_PVGCR0, 0x00);

            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_46_PORT_PAGE70_HDMI_PVGCR1, ~_BIT0, 0x00);
        }

        if((ucWDType & _HDMI_AV_MUTE_WD) == _HDMI_AV_MUTE_WD)
        {
            // Disable AV Mute Watch Dog
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_31_PORT_PAGE70_HDMI_WDCR0, ~_BIT7, 0x00);
        }
    }
}

#if(_D1_HDMI_2_0_SUPPORT == _ON)
//--------------------------------------------------
// Description  : TMDS Interrupt Process In PS/PD State(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1PSIntHandler_EXINT0(void) using 1
{
    BYTE pucBackUp[2];

    pucBackUp[0] = ScalerGetByte_EXINT(P70_39_HDMI_CTRL_39);
    pucBackUp[1] = ScalerGetByte_EXINT(P70_38_HDMI_CTRL_38);

    // Detect Source Write Read Request Enable Flag
    if((ScalerGetBit_EXINT(P70_25_HDMI_CTRL_25, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P70_26_HDMI_CTRL_26, _BIT3) == _BIT3))
    {
        // Clear Read Request Flag
        ScalerSetBit_EXINT(P70_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Set Read Request Enable
        SET_HDMI_2_0_RX1_RR_ENABLE();

        // Enable Test Read Request HW Auto Mode
        ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT1, _BIT1);

        // Enable CED Update Read Request Auto Mode
        ScalerSetBit_EXINT(P70_24_HDMI_CTRL_24, ~_BIT0, _BIT0);

        // Enable Read Request Done IRQ
        ScalerSetBit_EXINT(P70_1F_HDMI_CTRL_1F, ~_BIT3, _BIT3);
    }

    // Read Request Done into IRQ
    if((ScalerGetBit_EXINT(P70_1F_HDMI_CTRL_1F, _BIT3) == _BIT3) && (ScalerGetBit_EXINT(P70_1C_HDMI_CTRL_1C, _BIT7) == _BIT7))
    {
        // Clear Read Request Done Flag
        ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT7, _BIT7);

        // Read Request Outcome Processing
        ScalerTMDSRx1ReadRequestProc_EXINT0(ScalerGetByte_EXINT(P70_1C_HDMI_CTRL_1C) & 0x70);
    }

    // Detect HDMI HPD Rising to Falling into IRQ
    if(ScalerGetBit_EXINT(P70_23_HDMI_CTRL_23, (_BIT6 | _BIT1)) == (_BIT6 | _BIT1))
    {
        // Clear HPD IRQ Flag
        ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT1, _BIT1);

        if(ScalerGetBit_EXINT(P70_23_HDMI_CTRL_23, (_BIT2 | _BIT0)) == 0x00)
        {
            // Clear All Source Write SCDC Port Register
            ScalerSetBit_EXINT(P70_38_HDMI_CTRL_38, ~(_BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Clear HDMI 2.0 Read Request Enable
            CLR_HDMI_2_0_RX1_RR_ENABLE();

            // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

            // Enable Falling to Rising edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

            /*
            // Disable Test Read Request HW Auto Mode
            ScalerSetBit_EXINT(P70_1C_HDMI_CTRL_1C, ~_BIT1, 0x00);

            // Disable CED Update Read Request Auto Mode
            ScalerSetBit_EXINT(P70_24_HDMI_CTRL_24, ~_BIT0, 0x00);

            // Disable Character Error Detection Function
            ScalerSetBit_EXINT(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), 0x00);

            // Disable Lock Transition IRQ
            ScalerSetBit_EXINT(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

            ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Detect 3 Channel CDR Stable
            if((bit)ScalerTMDSRx1CheckCDRStable_EXINT(g_usTMDSRx1ClkCount) == _TRUE)
            {
                // Disable Rising to Falling IRQ, Set IRQ Status Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), (_BIT2 | _BIT1));

                // Enable Falling to Rising edge IRQ
                ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
            }
            */
        }
        else
        {
            /*
            // Enable CED Function
            ScalerSetBit_EXINT(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

            // Enable CED Lock Transition IRQ
            ScalerSetBit_EXINT(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            ScalerSetBit_EXINT(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // Enable SCDC Module
            ScalerSetBit_EXINT(P70_19_HDMI_CTRL_19, ~_BIT7, _BIT7);
            */

            // Disable Falling to Rising IRQ, Set IRQ Status Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~(_BIT6 | _BIT2 | _BIT1), _BIT1);

            // Enable Rising to Falling edge IRQ
            ScalerSetBit_EXINT(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);
        }
    }

    ScalerSetByte_EXINT(P70_38_HDMI_CTRL_38, pucBackUp[1]);
    ScalerSetByte_EXINT(P70_39_HDMI_CTRL_39, pucBackUp[0]);
}

//--------------------------------------------------
// Description  : TMDS Read Request Outcome Case Processing(EXINT0 Only)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1ReadRequestProc_EXINT0(BYTE ucRROutCome) using 1
{
    // Get Read Request Outcome Case
    switch(ucRROutCome)
    {
        case _HDMI_2_0_READ_REQUEST_ACK_DONE:
        case _HDMI_2_0_READ_REQUEST_ACK_STOP:

            break;

        case _HDMI_2_0_READ_REQUEST_NACK1:

            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // FW Manual Enable Read Request
                ScalerSetBit_EXINT(P70_1B_HDMI_CTRL_1B, ~_BIT7, _BIT7);
            }

            break;

        case _HDMI_2_0_READ_REQUEST_NACK2:

#if(_WD_TIMER_INT_SUPPORT == _ON)
            if(GET_HDMI_2_0_RX1_RR_ENABLE() == _TRUE)
            {
                // Enable Read Request Retry
                ScalerTimerWDActivateTimerEvent_EXINT0(10, _SCALER_WD_TIMER_EVENT_RX1_HDMI_RR_RETRY);
            }
#endif

            break;

        default:

            break;
    }
}

//--------------------------------------------------
// Description  : TMDS HPD IRQ Enable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1HDMI2HPDRRIRQEnable(bit bEnable)
{
    if(bEnable == _ENABLE)
    {
        // Set HPD Debounce = 700 Clock Cycle
        // Set HPD IRQ Detect Rising to Falling Edge IRQ
        ScalerSetBit(P70_23_HDMI_CTRL_23, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT5 | _BIT4 | _BIT3 | _BIT1));

        // Enable HDMI HPD IRQ Enable
        ScalerSetBit(P70_23_HDMI_CTRL_23, ~_BIT6, _BIT6);

        // Write 1 Clear Read Request
        ScalerSetBit(P70_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Enable HDMI 2.0 SCDC IIC Module
        ScalerSetBit(P70_19_HDMI_CTRL_19, ~_BIT7, _BIT7);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX1_RR_ENABLE();

        // Enable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P70_26_HDMI_CTRL_26, ~_BIT3, _BIT3);
    }
    else
    {
        // Write 1 Clear Read Request
        ScalerSetBit(P70_25_HDMI_CTRL_25, ~_BIT3, _BIT3);

        // Clear HDMI 2.0 Read Request Enable
        CLR_HDMI_2_0_RX1_RR_ENABLE();

        // Disable HDMI 2.0 Read Request Enable Detect IRQ
        ScalerSetBit(P70_26_HDMI_CTRL_26, ~_BIT3, 0x00);
    }
}
#endif // End of #if(_D1_HDMI_2_0_SUPPORT == _ON)

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get AMD SPD Info Contents
// Input Value  : Content of Interest
// Output Value : Content Value
//--------------------------------------------------
BYTE ScalerTMDSRx1HdmiGetAmdSpdInfo(EnumAmdSpdInfoContent enumContent)
{
    if(GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED() == _TRUE)
    {
        // Get AMD OUI
        ScalerGetDataPortByte(P70_CD_HDMI_PSAP, 0x90, 3, pData, _AUTOINC);
        if((pData[0] == 0x1A) && (pData[1] == 0x00) && (pData[2] == 0x00))
        {
            switch(enumContent)
            {
                case _SPD_INFO_FREESYNC_SUPPORT:

                    return ((bit)ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x95, _BIT0));

                case _SPD_INFO_FREESYNC_ENABLE:

                    return ((bit)ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x95, _BIT1));

                case _SPD_INFO_FREESYNC_ACTIVE:

                    return ((bit)ScalerGetDataPortBit(P70_CD_HDMI_PSAP, 0x95, _BIT2));

                case _SPD_INFO_FREESYNC_MIN_VFREQ:

                    ScalerGetDataPortByte(P70_CD_HDMI_PSAP, 0x96, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                case _SPD_INFO_FREESYNC_MAX_VFREQ:

                    ScalerGetDataPortByte(P70_CD_HDMI_PSAP, 0x97, 1, pData, _AUTOINC);

                    if(((WORD)pData[0] * 10) < _PANEL_FREESYNC_MIN_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MIN_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 0);
                    }
                    else if(((WORD)pData[0] * 10) > _PANEL_FREESYNC_MAX_FRAME_RATE)
                    {
                        pData[0] = _PANEL_FREESYNC_MAX_FRAME_RATE / 10;
                        DebugMessageRx1("Freesync SPD info abnormal", 1);
                    }

                    return pData[0];

                default:

                    return 0x00;
            }
        }
    }

    return 0x00;
}
#endif // End of #if(_HDMI_FREESYNC_SUPPORT == _ON)

#endif // End of #if(_D1_HDMI_SUPPORT == _ON)

//--------------------------------------------------
// Description  : TMDS Power Saving Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1PowerSavingProc(void)
{
    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_PS;

    ScalerTMDSRx1FreqDetectDisable();

    // Switch TMDS Input/Output to Auto
    ScalerSetBit(P70_A6_TMDS_OUTCTL, ~_BIT7, _BIT7);
    ScalerSetBit(P70_A7_TMDS_PWDCTL, ~_BIT4, _BIT4);

    // Set Freq. Stable Time: 5 times
    ScalerSetByte(P70_EC_HDMI_FREQDET_STABLE, 0x05);

    // Set Freq. Shift Offset to Max
    ScalerSetBit(P70_E7_HDMI_FREQDET_OFFSET, ~(_BIT2 | _BIT1 | _BIT0), 0x00);

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        // Set Upper Bound
        ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
        ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_PS_UPPER_BOUND));
    }
    else
#endif
    {
        // Set Upper Bound
        ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
        ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_PS_HIGH_SPEED_UPPER_BOUND));
    }

    // Set Lower Bound
    ScalerSetByte(P70_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
    ScalerSetByte(P70_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_PS_LOWER_BOUND));
}

//--------------------------------------------------
// Description  : TMDS Power Off Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1PowerOffProc(void)
{
    // Disable EDID read/ SCL toggle IRQ
    MCU_FFE5_DDC1_EDID_IRQ = ((MCU_FFE5_DDC1_EDID_IRQ & ~(_BIT3 | _BIT1)) | (_BIT2 | _BIT0));

    ScalerTMDSRx1FreqDetectDisable();
}

//--------------------------------------------------
// Description  : TMDS Freq. Detection IRQ Disable and Clear Clock Counter
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1FreqDetectDisable(void)
{
    // Disable TMDS Freq. Detect IRQ
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);
    ScalerSetBit(P70_EF_HDMI_ERROR_TH, ~_BIT7, 0x00);

    // Clear TMDS Clk Count
    g_usTMDSRx1ClkCount = 0;

#if(_D1_HDMI_2_0_SUPPORT == _ON)
    // Disable CED Function
    ScalerSetBit(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), 0x00);

    // Pop Up CED Error For Clear Error Counter
    ScalerSetBit(P70_0C_HDMI_CTRL_0C, ~_BIT7, _BIT7);

    // Disable CED Lock Transition IRQ & Flag
    ScalerSetBit(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), 0x00);
#endif
}

//--------------------------------------------------
// Description  : Process Required when Switched to Active State
// Input Value  : Input Source
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1FirstActiveProc(BYTE ucSourceType)
{
    ucSourceType = ucSourceType;
}

//--------------------------------------------------
// Description  : Initial Setting for TMDS Scanning Port(Power Normal)
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1TMDSScanInitial(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // Set Power Saving DDC Debounce Counter
    g_usDDCDebounceCnt = _TMDS_DDC_DEBOUNCE_NORMAL;

    ScalerTMDSRx1Initial(ucInputPort);

    ScalerTMDSRx1InterruptInitial();
}

//--------------------------------------------------
// Description  : Signal Detection for TMDS(Power Saving)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx1TMDSPSPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX1_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx1("7. PowerSaving D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX1_TOGGLE_Z0();
#endif
        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
    {
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;
    }

    // Reset Freq. Detect Counter(Toggle) & Choose Measure Clk to TMDS Clk
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~(_BIT7 | _BIT5 | _BIT4), 0x00);
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

    // Clear Freq. Stable Flag
    ScalerSetBit(P70_EF_HDMI_ERROR_TH, ~_BIT6, _BIT6);

    // Clear Unstable Flag
    ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT2, _BIT2);

    // Delay enough time for freq. measure (calculated for measure 5 times)
    ScalerTimerDelayXms(5);

    // Detect Freq. Measure Stable
    if((ScalerGetBit(P70_E6_HDMI_FREQDET_CTRL, (_BIT6 | _BIT2)) == _BIT6) && (ScalerGetBit(P70_EF_HDMI_ERROR_TH, _BIT6) == _BIT6))
    {
#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
        SET_TMDS_RX1_TOGGLE_Z0();
#endif
        return _TRUE;
    }
    else
    {
        // Disable Freq. Detection
        ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);

        return _FALSE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Signal PreDetection for TMDS(Power Normal)
// Input Value  : Input Port
// Output Value : True : TMDS Signal Detected
//              : False : No Signal
//--------------------------------------------------
bit ScalerTMDSRx1TMDSNormalPreDetect(BYTE ucInputPort)
{
    ucInputPort = ucInputPort;

    // DDC handshake Detected
    if(GET_TMDS_RX1_DDC_DETECTED() == _TRUE)
    {
        DebugMessageRx1("7. Normal D1 DDC", 0);

        CLR_TMDS_RX1_DDC_DETECTED();

        return _TRUE;
    }

    // Enable DDC Toggle IRQ
    if(((MCU_FFE5_DDC1_EDID_IRQ & _BIT3) != _BIT3) && (GET_TMDS_RX1_DDC_DETECTED() != _TRUE))
    {
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
        MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

        CLR_TMDS_RX1_DDC_DETECTED();
    }

    ScalerTimerDelayXms(6);

    if(GET_TMDS_RX1_PHY_SET() == _TRUE)
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : TMDS Port Source/Sync Scanning and Setting
// Input Value  : Input Port
// Output Value : Source DVI --> DVI Format
//                Source HDMI --> HDMI Format
//                Source None --> No Stable Sync
//--------------------------------------------------
BYTE ScalerTMDSRx1TMDSScanInputPort(BYTE ucInputType)
{
    BYTE ucTMDSType = _SOURCE_NONE;

    BYTE ucTMDSVideoDataType = _TMDS_VIDEO_DATA_NONE;

    ucInputType = ucInputType;

    if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        return _SOURCE_NONE;
    }

    if(GET_TMDS_RX1_PHY_SET() == _TRUE)
    {
        // Set DIGITAL_PORT_SWITCH Flag for MHL
        SET_DIGITAL_PORT_SWITCH_TO_D1();

        // Delay for PHY Stable
        ScalerTimerDelayXms(2);

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        if((ScalerTMDSRx1CheckCDRStable(g_usTMDSRx1ClkCount) == _FALSE) ||
           ((GET_D1_TMDS_MODE() == _TMDS_MHL_MODE) && (ScalerMHLRx1DetectClkMode() == _FALSE)) ||
           (ScalerTMDSRx1TMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))
#else
        if((ScalerTMDSRx1CheckCDRStable(g_usTMDSRx1ClkCount) == _FALSE) ||
           ((GET_D1_TMDS_MODE() == _TMDS_MHL_MODE) && (ScalerMHLRx1DetectClkMode() == _FALSE)))
#endif

#else // Else of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

#if(_D1_HDMI_2_0_SUPPORT == _ON)

        if((ScalerTMDSRx1CheckCDRStable(g_usTMDSRx1ClkCount) == _FALSE) || (ScalerTMDSRx1TMDSVideoDetect(_WAIT) == _TMDS_VIDEO_DATA_NONE))
#else
        if(ScalerTMDSRx1CheckCDRStable(g_usTMDSRx1ClkCount) == _FALSE)
#endif

#endif // End of #if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        {

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
            {
                // Set Upper Bound
                ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
                ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_MHL_FREQ_NORMAL_UPPER_BOUND));
            }
            else
#endif
            {
                // Set Upper Bound
                ScalerSetByte(P70_E8_HDMI_FREQDET_UPPER_M, HIBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
                ScalerSetByte(P70_E9_HDMI_FREQDET_UPPER_L, LOBYTE(_TMDS_FREQ_NORMAL_HIGH_SPEED_UPPER_BOUND));
            }

            // Set Lower Bound
            ScalerSetByte(P70_EA_HDMI_FREQDET_LOWER_M, HIBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));
            ScalerSetByte(P70_EB_HDMI_FREQDET_LOWER_L, LOBYTE(_TMDS_FREQ_NORMAL_LOWER_BOUND));

            // Set Stable Time (0x7F = about 5ms)
            ScalerSetByte(P70_EC_HDMI_FREQDET_STABLE, 0x7F);

#if(_D1_HDMI_2_0_SUPPORT == _ON)

            if((GET_TMDS_RX1_HIGH_SPEED_MODE() == _FALSE) && (GET_D1_TMDS_MODE() != _TMDS_MHL_MODE)) // HDMI mode
            {
                DebugMessageRx1("TMDS Rx1 First 1:10 set phy not success", 1);

                SET_TMDS_RX1_HIGH_SPEED_MODE();
            }
            else
            {
                CLR_TMDS_RX1_HIGH_SPEED_MODE();
            }
#endif
            CLR_TMDS_RX1_PHY_SET();

            // Disable Freq. Unstable IRQ
            ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT1, 0x00);

            // Reset Freq. Detect Counter(Toggle)
            ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, 0x00);
            ScalerSetBit(P70_E6_HDMI_FREQDET_CTRL, ~_BIT7, _BIT7);

            // Enable Freq. Stable IRQ
            ScalerSetBit(P70_EF_HDMI_ERROR_TH, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

            return _SOURCE_NONE;
        }

        // Clear RGBHV Flag
        ScalerSetBit(P70_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        // Clear Info Packet SRAM
        ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT3, _BIT3);
        ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT3, 0x00);

        // Clear AVI infoframe & GCP packet Detection Flag
        ScalerSetBit(P70_CC_HDMI_GPVS, ~_BIT6, _BIT6);
        ScalerSetBit(P70_CC_HDMI_GPVS, ~_BIT5, _BIT5);

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        // Clear DRR flag
        CLR_FREESYNC_ENABLED();

        // Clear SPD infoframe
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6), _BIT7);
#endif

        DebugMessageRx1("9. Freq Check Pass => Pixel Clock", GET_D1_INPUT_PIXEL_CLK());
        DebugMessageRx1("7. TMDS Lane0 LE Min", g_pucTMDSRx1LEMin[0]);
        DebugMessageRx1("7. TMDS Lane1 LE Min", g_pucTMDSRx1LEMin[1]);
        DebugMessageRx1("7. TMDS Lane2 LE Min", g_pucTMDSRx1LEMin[2]);
        DebugMessageRx1("7. TMDS Lane0 LE Max", g_pucTMDSRx1LEMax[0]);
        DebugMessageRx1("7. TMDS Lane1 LE Max", g_pucTMDSRx1LEMax[1]);
        DebugMessageRx1("7. TMDS Lane2 LE Max", g_pucTMDSRx1LEMax[2]);

#if(_D1_HDMI_2_0_SUPPORT == _ON)

        // Disable Reset HDMI/DVI Format
        ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

        // Clear CED Lock Transition Flag
        ScalerSetBit(P70_17_HDMI_CTRL_17, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Enable Character Error Detection Function & Valid Flag
        ScalerSetBit(P70_0B_HDMI_CTRL_0B, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2));

        // Enable Character Error Detction Function Lock Transition IRQ
        ScalerSetBit(P70_18_HDMI_CTRL_18, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

        // Set HDMI 2.0 Character Error Detection Function Lock Transition Error Boundary
        ScalerSetBit(P70_14_HDMI_CTRL_14, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (GET_D1_INPUT_PIXEL_CLK() / 10) >> 8);
        ScalerSetByte(P70_15_HDMI_CTRL_15, (GET_D1_INPUT_PIXEL_CLK() / 10));

        DebugMessageRx1("HDMI 2.0 Error Boundary set High Byte", ScalerGetByte(P70_14_HDMI_CTRL_14));
        DebugMessageRx1("HDMI 2.0 Error Boundary set Low Byte", ScalerGetByte(P70_15_HDMI_CTRL_15));
#endif

        if(ScalerTMDSRx1FormatDetect() == _SOURCE_HDMI)
        {
            DebugMessageRx1("Format Detect HDMI", 0x00);

#if(_TMDS_HDCP_FEATURE == _HDCP_FEATURE_BY_INPUT)
            ScalerSetDataPortBit(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, ~_BIT1, _BIT1);
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
            ScalerSetDataPortBit(P70_C3_HDCP_AP, _P70_C4_PT_40_PORT_PAGE70_BCAPS, ~_BIT1, 0x00);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING)
            {
                ucTMDSType = _SOURCE_HDMI;
            }
            else
#endif
            {
                ucTMDSType = _SOURCE_DVI;
            }
        }

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        // Mute ASUS Padfone until Source Read Ri Done (Incase of Color Format Error)
        if(((GET_MHL_RX1_ADOPTER_ID_HBYTE() == _ASUS_PADFONE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX1_ADOPTER_ID_LBYTE() == _ASUS_PADFONE2_ADOPTER_ID_LBYTE)) &&
           !(ScalerGetBit(P70_A9_TMDS_ABC0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)))
        {
            return _SOURCE_NONE;
        }
#endif

        ucTMDSVideoDataType = ScalerTMDSRx1TMDSVideoDetect(_WAIT);

        if(ucTMDSVideoDataType == _TMDS_VIDEO_DATA_DE_ONLY)
        {
            DebugMessageRx1("DE Only Mode", 0x00);

#if(_DVI_DE_ONLY_SUPPORT == _ON)
            if(ucTMDSType == _SOURCE_DVI)
            {
                // Enable DE Only Mode
                ScalerSetBit(P70_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
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
            ScalerSetBit(P70_A7_TMDS_PWDCTL, ~_BIT7, _BIT7);
        }
        else
        {
            return _SOURCE_NONE;
        }

        if(GET_D1_INPUT_PIXEL_CLK() > 3400)
        {
            // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
            // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
            ScalerSetBit(P7A_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P7A_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), _BIT0);
            ScalerSetBit(P7A_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), _BIT0);
        }
        else
        {
            // [1] De_inverse = 1'b1 --> Adapation Only for Data Area (Transition Minimum)
            // [0] De_brank_en = 1'b1 --> Enable Blank Function of gdi_de
            ScalerSetBit(P7A_AF_L0_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7A_BF_L1_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P7A_CF_L2_GDI_DE, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
        }

#if(_D1_HDMI_SUPPORT == _ON)
        if(ucTMDSType == _SOURCE_HDMI)
        {
            // HDMI packet detect --> AVI infoframe & GCP packet
            ScalerTMDSRx1HdmiPacketDetect(_WAIT);

            ScalerSyncTMDSRx1HdmiVideoSetting();

            SET_COLOR_DEPTH(_D1_INPUT_PORT, ScalerTMDSRx1HdmiGetColorDepth());

            if((GET_COLOR_DEPTH(_D1_INPUT_PORT) != _COLOR_DEPTH_8_BITS) && (GET_COLOR_SPACE(_D1_INPUT_PORT) != _COLOR_SPACE_YCBCR422))
            {
                DebugMessageRx1("Deep Color Mode Detected", GET_COLOR_DEPTH(_D1_INPUT_PORT));
                SET_D1_INPUT_PIXEL_CLK((GET_D1_INPUT_PIXEL_CLK() << 3) / GET_COLOR_DEPTH(_D1_INPUT_PORT));

                if(ScalerTMDSRx1HdmiDeepColorProc(g_usTMDSRx1ClkCount) == _FALSE)
                {
                    return _SOURCE_NONE;
                }

                // Turn On Deep Color Block
                ScalerSetBit(P70_B5_TMDS_UDC0, ~_BIT7, _BIT7);

                if(GET_COLOR_SPACE(_D1_INPUT_PORT) == _COLOR_SPACE_YCBCR420)
                {
                    // HDMI Output Div2 Enable
                    ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT7, _BIT7);
                }
                else
                {
                    // HDMI Output Div2 Disable
                    ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT7, 0x00);
                }
            }
            else
            {
                // Turn off Deep Color Block
                ScalerSetBit(P70_B5_TMDS_UDC0, ~_BIT7, 0x00);

                // HDMI Output Div2 Disable
                ScalerSetBit(P70_AD_TMDS_CPS, ~_BIT7, 0x00);
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(ScalerTMDSRx1HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_SUPPORT) == _ENABLE)
            {
                SET_HDMI_FREESYNC_ENABLED();

                // Get SPD Free Sync Vfreq Max
                g_usFREESYNCVFreq = (WORD)ScalerTMDSRx1HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_MAX_VFREQ) * 10;

                // Disable DE Only Mode
                ScalerSetBit(P70_A7_TMDS_PWDCTL, ~_BIT7, 0x00);
            }
#endif
        }
        else
        {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            // Guard Band reference disable for data remapping
            ScalerSetBit(P75_B2_MHL_CTRL_12, ~_BIT7, 0x00);
#endif

            CLR_HDMI_RX1_AVI_INFO_FRAME_RECEIVED();

            CLR_HDMI_RX1_GCP_RECEIVED();

            // Disable All WD when DVI
            ScalerTMDSRx1HdmiWatchDog((_HDMI_AVI_INFO_VARIATION_WD | _HDMI_AV_MUTE_WD), _DISABLE);

            ScalerTMDSRx1DviVideoSetting();

            SET_COLOR_DEPTH(_D1_INPUT_PORT, _COLOR_DEPTH_8_BITS);

            // Turn off Deep Color Block
            ScalerSetBit(P70_B5_TMDS_UDC0, ~_BIT7, 0x00);
        }
#else

        ScalerTMDSRx1DviVideoSetting();

        SET_COLOR_DEPTH(_D1_INPUT_PORT, _COLOR_DEPTH_8_BITS);

        // Turn off Deep Color Block
        ScalerSetBit(P70_B5_TMDS_UDC0, ~_BIT7, 0x00);
#endif

        // Enable Video Output
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_30_PORT_PAGE70_HDMI_AVMCR, ~_BIT3, _BIT3);
        ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_80_PORT_PAGE70_HDMI_DPC_SET0, ~_BIT7, _BIT7);

        // Enable RGB Clk Output
        ScalerSetBit(P70_A6_TMDS_OUTCTL, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT6 | _BIT5 | _BIT4 | _BIT3));

        return ucTMDSType;
    }

    return _SOURCE_NONE;
}

//--------------------------------------------------
// Description  : Detect TMDS Format
// Input Value  : None
// Output Value : Return DVI or HDMI format
//--------------------------------------------------
BYTE ScalerTMDSRx1FormatDetect(void)
{
    // Polling at least 3 frame for HW auto detect TMDS format
    if(ScalerTimerPollingFlagProc(130, P70_CB_HDMI_SR, _BIT0, _TRUE) == _TRUE)
    {
        ScalerSetBit(P70_AF_TMDS_WDC, ~_BIT0, 0x00);

#if(_D1_HDMI_2_0_SUPPORT == _ON)
        if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
            // Check if HDMI 2.0 ON
            if(ScalerGetBit(P70_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                // Set Manual Format to HDMI
                ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));

                // Toggle HW Format Detect Flag Reset
                ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                SET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING();

                ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT);
            }

            // Detect Scrambling Control Symbol
            if(ScalerGetBit(P70_01_HDMI_CTRL_01, _BIT3) == _BIT3)
            {
                // Enable Scrambling Status in SCDC
                ScalerSetDataPortBit(P70_39_HDMI_CTRL_39, _P70_3A_PT_21_PORT_PAGE70_HDMI_SCDC_21, ~_BIT0, _BIT0);
            }
        }
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)

        if(GET_D1_TMDS_MODE() == _TMDS_MHL_MODE)
        {
            // Set Manual Format to HDMI
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT3 | _BIT2));
        }
#endif
        return _SOURCE_HDMI;
    }
    else
    {
        ScalerSetBit(P70_AF_TMDS_WDC, ~_BIT0, _BIT0);

        if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
        {
#if(_D1_HDMI_2_0_SUPPORT == _ON)
            if(ScalerGetBit(P70_00_HDMI_CTRL_00, _BIT0) == _BIT0)
            {
                ScalerTimerCancelTimerEvent(_SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT);
            }
#endif
            // Set Format Detect HW Auto Mode
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);
        }
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        else
        {
            // Manual Set to DVI Mode
            ScalerSetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), _BIT3);
        }
#endif
        return _SOURCE_DVI;
    }
}

//--------------------------------------------------
// Description  : Check whether HDCP is enabled
// Input Value  : None
// Output Value : TRUE => HDCP Enabled
//--------------------------------------------------
bit ScalerTMDSRx1HdcpEnabled(void)
{
    BYTE pucHDCPFrameCount[2];
    memset(pucHDCPFrameCount, 0, sizeof(pucHDCPFrameCount));

    ScalerGetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_C0_PORT_PAGE70_HDCP_FCR, 1, &pucHDCPFrameCount[0], _NON_AUTOINC);

    // Wait 2Vsync to make sure frame counter changing, and timeout 45ms (margin + 1/24 frame+rate)
    ScalerSetBit(P70_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
    ScalerTimerPollingFlagProc(45, P70_A4_TMDS_CTRL, _BIT3, _TRUE);
    ScalerSetBit(P70_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT3);
    ScalerTimerPollingFlagProc(45, P70_A4_TMDS_CTRL, _BIT3, _TRUE);

    ScalerGetDataPortByte(P70_C3_HDCP_AP, _P70_C4_PT_C0_PORT_PAGE70_HDCP_FCR, 1, &pucHDCPFrameCount[1], _NON_AUTOINC);

    if(pucHDCPFrameCount[0] != pucHDCPFrameCount[1])
    {
        return _TRUE;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Detect TMDS video mode
// Input Value  : bWait => Whether to wait then read
// Output Value : TMDS video type
//--------------------------------------------------
BYTE ScalerTMDSRx1TMDSVideoDetect(bit bWait)
{
    BYTE ucTemp = _TMDS_VIDEO_DATA_NONE;

    if(bWait == _WAIT)
    {
        // Wait at least 1 frame for HW auto update TMDS video RGBHV valid value
        ScalerTimerPollingFlagProc(45, P70_A4_TMDS_CTRL, _BIT3, _TRUE);

        // Wait for HW update DE flag
        if(ScalerTimerPollingFlagProc(20, P70_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5), _TRUE) == _TRUE)
        {
            // H/Vsync received
            if(ScalerGetBit(P70_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        CLR_TMDS_RX1_RGBHV_DETECTING();

        return ucTemp;
    }
    else
    {
        // R/G/B data detected
        if(ScalerGetBit(P70_A4_TMDS_CTRL, (_BIT7 | _BIT6 | _BIT5)) == (_BIT7 | _BIT6 | _BIT5))
        {
            // H/Vsync received
            if(ScalerGetBit(P70_A4_TMDS_CTRL, (_BIT4 | _BIT3)) == (_BIT4 | _BIT3))
            {
                ucTemp = _TMDS_VIDEO_DATA_RGBHV;
            }
            else
            {
                ucTemp = _TMDS_VIDEO_DATA_DE_ONLY;
            }
        }
        else
        {
            ucTemp = _TMDS_VIDEO_DATA_NONE;
        }

        // Clear video Detection Flag
        ScalerSetBit(P70_A4_TMDS_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3));

        SET_TMDS_RX1_RGBHV_DETECTING();

        // Activate TMDS video Detection Event
        ScalerTimerActiveTimerEvent(SEC(0.045), _SCALER_TIMER_EVENT_RX1_TMDS_VIDEO_DETECT);

        return ucTemp;
    }
}

//--------------------------------------------------
// Description  : TMDS video Detect Event
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerTMDSRx1TMDSVideoDetectEvent(void)
{
    CLR_TMDS_RX1_RGBHV_DETECTING();
}

//--------------------------------------------------
// Description  : On Line Check TMDS stability
// Input Value  : ucSourceType --> Source Type
// Output Value : True --> TMDS Stable
//                False --> TMDS Unstable
//--------------------------------------------------
bit ScalerTMDSRx1TMDSStableDetect(BYTE ucSourceType)
{
    // CLR SCL/SDA Toggle Flag
    CLR_TMDS_RX1_DDC_DETECTED();

    if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() != _TMDS_HPD_NONE)
    {
        DebugMessageRx1("Rx1 HPD Toggle!!", 0);
        return _FALSE;
    }

    if(ScalerTMDSRx1CheckCDRStable(g_usTMDSRx1ClkCount) == _FALSE)
    {
        DebugMessageRx1("CDR Unstable!!", ucSourceType);
        return _FALSE;
    }

    if(ScalerGetBit(P70_A6_TMDS_OUTCTL, _BIT3) == 0x00)
    {
        DebugMessageRx1("TMDS Clock Output has been disable", ucSourceType);
        return _FALSE;
    }

#if(_D1_HDMI_2_0_SUPPORT == _ON)

    if((GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE) && (ScalerGetBit(P70_00_HDMI_CTRL_00, _BIT0) == _BIT0))
    {
        if(ucSourceType == _SOURCE_HDMI)
        {
            if(GET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING() == _FALSE)
            {
                if(ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_00_PORT_PAGE70_HDMI_SCR, _BIT3) != _BIT3)
                {
                    return _FALSE;
                }
                else
                {
                    if(ScalerGetBit(P70_CB_HDMI_SR, _BIT0) == 0x00)
                    {
                        DebugMessageRx1("TMDS Format Changed", ucSourceType);

                        return _FALSE;
                    }
                    else
                    {
                        // Toggle HW Format Detect Flag Reset
                        ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), _BIT7);
                        ScalerSetBit(P70_01_HDMI_CTRL_01, ~(_BIT7 | _BIT3), 0x00);

                        SET_TMDS_RX1_HDMI_2_0_FORMAT_RESET_WAITING();

                        ScalerTimerReactiveTimerEvent(130, _SCALER_TIMER_EVENT_RX1_HDMI2_FORMAT_RESET_WAIT);
                    }
                }
            }
        }
        else
        {
            if(ScalerGetBit(P70_CB_HDMI_SR, _BIT0) == _BIT0)
            {
                DebugMessageRx1("TMDS Format Changed", ucSourceType);
                return _FALSE;
            }
        }
    }
    else
#endif
    {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
        if((GET_TMDS_RX1_CLK_MODE() == _TMDS_24BIT_PHY_SETTING) ||
           ((GET_TMDS_RX1_CLK_MODE() == _TMDS_MHL_PPMODE_PHY_SETTING) && (ucSourceType == _SOURCE_DVI)))
#endif
        {
            if(ucSourceType == _SOURCE_HDMI)
            {
                if(ScalerGetBit(P70_CB_HDMI_SR, _BIT0) == 0x00)
                {
                    DebugMessageRx1("TMDS Format Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
                if(ScalerGetBit(P70_CB_HDMI_SR, _BIT0) == _BIT0)
                {
                    DebugMessageRx1("TMDS Format Changed", ucSourceType);
                    return _FALSE;
                }
            }
        }
    }

    if(GET_TMDS_RX1_Z0_ASSERTED() == _TRUE)
    {
        if((ScalerGetBit(P70_A9_TMDS_ABC0, _BIT6) == _BIT6) && (ScalerGetBit(P70_A9_TMDS_ABC0, (_BIT7 | _BIT5)) != (_BIT7 | _BIT5)))
        {
            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            CLR_TMDS_RX1_Z0_ASSERTED();

            DebugMessageRx1("7. HDCP Abnormal !!!!!", 0);

            // MHL mode of MHL PORT will not return FALSE
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                return _FALSE;
            }
#else
            return _FALSE;
#endif
        }
        else if((ScalerGetBit(P70_A9_TMDS_ABC0, (_BIT7 | _BIT5)) == (_BIT7 | _BIT5)))
        {
            CLR_TMDS_RX1_Z0_ASSERTED();

            DebugMessageRx1("7. HDCP Normal", 0);
        }
    }

    if(ucSourceType == _SOURCE_DVI)
    {
        if(GET_TMDS_RX1_RGBHV_DETECTING() == _FALSE)
        {
            // TMDS Video Detected
            if(ScalerTMDSRx1TMDSVideoDetect(_NOT_WAIT) != _TMDS_VIDEO_DATA_RGBHV)
            {
                DebugMessageRx1("TMDS Video format changed", ucSourceType);

#if(_DVI_DE_ONLY_SUPPORT == _OFF)
                return _FALSE;
#endif
            }
        }
    }

#if(_D1_HDMI_SUPPORT == _ON)

    if(ucSourceType == _SOURCE_HDMI)
    {
        if(GET_HDMI_RX1_PACKET_DETECTING() == _FALSE)
        {
            // HDMI Packet Detected
            ScalerTMDSRx1HdmiPacketDetect(_NOT_WAIT);

            if(GET_HDMI_RX1_AVI_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if(ScalerSyncTMDSRx1HdmiColorInfoChanged() == _TRUE)
                {
                    DebugMessageRx1("Color Info Changed", ucSourceType);
                    return _FALSE;
                }

                if(ScalerTMDSRx1HdmiAviPixelRepInfoChanged() == _TRUE)
                {
                    DebugMessageRx1("Pixel Repetition Info Changed", ucSourceType);
                    return _FALSE;
                }
            }
            else
            {
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
                if(GET_TMDS_RX1_CLK_MODE() == _TMDS_24BIT_PHY_SETTING)
#endif
                {
                    if(GET_COLOR_SPACE(_D1_INPUT_PORT) != _COLOR_SPACE_RGB)
                    {
                        DebugMessageRx1("HDMI Info Frame Not Received and not RGB", ucSourceType);
                        return _FALSE;
                    }
                }

#if(_RGB_QUANTIZATION_RANGE_SUPPORT == _ON)
                if(GET_COLOR_RGB_QUANTIZATION_RANGE(_D1_INPUT_PORT) != _RGB_QUANTIZATION_RESERVED)
                {
                    DebugMessageRx1("No Quantization Range Specified", ucSourceType);
                    return _FALSE;
                }
#endif

                if(GET_TMDS_RX1_AVI_PIXEL_REPETITION() != _AVI_PIXEL_REPETITION_0)
                {
                    DebugMessageRx1("Pixel Repetition Not Received and not Pixel repetition 0", ucSourceType);
                    return _FALSE;
                }
            }

            if((ScalerGetDataPortBit(P70_C9_HDMI_AP, _P70_CA_PT_41_PORT_PAGE70_HDMI_VWDSR, _BIT0) == _BIT0) && (ScalerGetBit(P70_CC_HDMI_GPVS, _BIT0) == _BIT0))
            {
                DebugMessageRx1("HDMI AVI info frame has changed", ucSourceType);
                return _FALSE;
            }

            if(GET_HDMI_RX1_GCP_RECEIVED() == _TRUE)
            {
                if((GET_COLOR_SPACE(_D1_INPUT_PORT) != _COLOR_SPACE_YCBCR422) && (ScalerTMDSRx1HdmiGetColorDepth() != GET_COLOR_DEPTH(_D1_INPUT_PORT)))
                {
                    DebugMessageRx1("Color Depth Has Changed", GET_COLOR_DEPTH(_D1_INPUT_PORT));
                    return _FALSE;
                }
            }
            else
            {
                if((GET_COLOR_SPACE(_D1_INPUT_PORT) != _COLOR_SPACE_YCBCR422) && (GET_COLOR_DEPTH(_D1_INPUT_PORT) != _COLOR_DEPTH_8_BITS))
                {
                    DebugMessageRx1("HDMI GCP PACKET Not Received and not 8 bit", ucSourceType);
                    return _FALSE;
                }
            }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
            if(GET_TMDS_RX1_SPD_INFO_FRAME_RECEIVED() == _TRUE)
            {
                if((bit)ScalerTMDSRx1HdmiGetAmdSpdInfo(_SPD_INFO_FREESYNC_SUPPORT) != GET_HDMI_FREESYNC_ENABLED())
                {
                    DebugMessageRx1("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
            else
            {
                if(GET_HDMI_FREESYNC_ENABLED() == _TRUE)
                {
                    DebugMessageRx1("HDMI Freesync Status Change", GET_HDMI_FREESYNC_ENABLED());
                    return _FALSE;
                }
            }
#endif
        }

#if(_HDMI_FREESYNC_SUPPORT == _ON)
        if(GET_TMDS_RX1_FREESYNC_SUPPORT() != GET_FREESYNC_SUPPORT())
        {
            SET_TMDS_RX1_FREESYNC_SUPPORT(GET_FREESYNC_SUPPORT());
            SET_TMDS_RX1_HPD_TRIGGER_EVENT(_TMDS_HPD_NORMAL);

            // MHL mode of MHL PORT will not return FALSE
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
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

    if(GET_TMDS_RX1_TOGGLE_Z0() == _TRUE)
    {
        SET_TMDS_RX1_TOGGLE_Z0_EVENT();

        return _FALSE;
    }

#endif

    return _TRUE;
}

//--------------------------------------------------
// Description  : TMDS Hot Plug Event
// Input Value  : None
// Output Value :
//--------------------------------------------------
void ScalerTMDSRx1HotPlugEvent(void)
{
    BYTE ucZ0Status = 0;

    // MHL mode of MHL PORT can not pull HPD
#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE) && (GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE))
#else
    if((GET_HDMI_HOTPLUG_TOGGLE() == _TRUE) && (GET_D1_CABLE_STATUS() == _TRUE))
#endif
    {
        // Save Z0 Status
        ucZ0Status = ScalerGetBit(PB0_A2_CMU_02, (_BIT7 | _BIT6 | _BIT5 | _BIT4));

        // Disable Z0
        ScalerSetBit(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

        // ACER mode and DVI port will only toggle Z0 130ms
#if((_D1_INPUT_PORT_TYPE == _D1_DVI_PORT) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
        if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
        {
            ScalerTimerDelayXms(130);
        }
        else
#endif
        {
            // HPD Low
            PCB_D1_HOTPLUG(_D1_HOT_PLUG_LOW);

            // wait
            if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_NORMAL)
            {
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
            }
            else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_HDCP_2_2)
            {
                ScalerTimerDelayXms(1000);
            }
            else if(GET_TMDS_RX1_HPD_TRIGGER_EVENT() == _TMDS_HPD_ACER)
            {
                ScalerTimerDelayXms(130);
            }
            else
            {
                ScalerTimerDelayXms(GET_HDMI_HOTPLUG_TIME());
            }

            // HPD High
            PCB_D1_HOTPLUG(_D1_HOT_PLUG_HIGH);
        }

        // Restore Z0 Status
        ScalerSetBit(PB0_A2_CMU_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), ucZ0Status);

        DebugMessageRx1("Rx1 HPD Toggle!!", 0);
    }
    else if(GET_D1_CABLE_STATUS() == _FALSE)
    {
        // DDC reset
        MCU_FF2D_DDC1_DDC_CONTROL_1 |= _BIT1;
    }

#if(_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON)
    if(GET_TMDS_RX1_TOGGLE_Z0_EVENT() == _TRUE)
    {
        CLR_TMDS_RX1_TOGGLE_Z0();
        CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
    }
#endif

    CLR_TMDS_RX1_HPD_TRIGGER_EVENT();
}
#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

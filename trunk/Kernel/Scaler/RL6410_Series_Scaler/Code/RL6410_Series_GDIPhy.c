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
// ID Code      : RL6410_Series_GDIPhy.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _MHL_1K                                 7
#define _MHL_100K                               8


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
void ScalerGDIPhyBandgap(bit bSelect);

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
void ScalerGDIPhyRx0Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx0PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx0Power(EnumPowerAction enumPowerAction);
#endif

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
void ScalerGDIPhyRx1Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx1PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx1Power(EnumPowerAction enumPowerAction);
#endif

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
void ScalerGDIPhyRx2Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx2PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx2Power(EnumPowerAction enumPowerAction);
#endif

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
void ScalerGDIPhyRx3Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx3PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx3Power(EnumPowerAction enumPowerAction);
#endif

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
void ScalerGDIPhyRx4Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx4PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx4Power(EnumPowerAction enumPowerAction);
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
void ScalerGDIPhyRx5Z0Switch(BYTE ucPortSelect, bit bSelect);
void ScalerGDIPhyRx5PowerProc(EnumPowerAction enumPowerAction);
void ScalerGDIPhyRx5Power(EnumPowerAction enumPowerAction);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : GDI Bandgap
// Input Value  : ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyBandgap(bit bSelect)
{
    BYTE ucTemp = 0;

    // [4] reg_en_vtest_hiz = 0 --> Enable Vtest HIZ Mode
    ScalerSetBit(P1D_1C_CMU_02, ~_BIT4, 0x00);
    ScalerSetBit(P7A_1C_CMU_02, ~_BIT4, 0x00);
    ScalerSetBit(P7B_1C_CMU_02, ~_BIT4, 0x00);
    ScalerSetBit(P7C_1C_CMU_02, ~_BIT4, 0x00);
    ScalerSetBit(P7D_1C_CMU_02, ~_BIT4, 0x00);
    ScalerSetBit(P7E_1C_CMU_02, ~_BIT4, 0x00);

    // [7:6] reg_offcal_range = 2'b11 --> 75uA
    ScalerSetBit(P1D_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P7A_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P7B_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P7C_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P7D_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerSetBit(P7E_26_KOFFSET_02, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

    // [0] PLL_WD_EN = 1'b0 --> Disable WD
    ScalerSetBit(P1D_0F_WD, ~_BIT0, 0x00);
    ScalerSetBit(P7A_0F_WD, ~_BIT0, 0x00);
    ScalerSetBit(P7B_0F_WD, ~_BIT0, 0x00);
    ScalerSetBit(P7C_0F_WD, ~_BIT0, 0x00);
    ScalerSetBit(P7D_0F_WD, ~_BIT0, 0x00);
    ScalerSetBit(P7E_0F_WD, ~_BIT0, 0x00);

    // [7:5] reg_adp_time = 3'b010 --> DP PHY DFE delay_time = 16*(1/14.318)*(reg_adp_time[2:0]+1) = 3.35us
    ScalerSetBit(P1D_2D_ANA_CDR_02, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);
    ScalerSetBit(P7A_2D_ANA_CDR_02, ~(_BIT7 | _BIT6 | _BIT5), _BIT6);

    // [6:4] reg_adp_time = 3'b010 --> HDMI PHY DFE delay_time = 16*(1/14.318)*(reg_adp_time[2:0]+1) = 3.35us
    ScalerSetBit(P7B_2C_ANA_CDR_02, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(P7C_2C_ANA_CDR_02, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(P7D_2C_ANA_CDR_02, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);
    ScalerSetBit(P7E_2C_ANA_CDR_02, ~(_BIT6 | _BIT5 | _BIT4), _BIT5);

    // [5] reg_Hybrid = 1'b0 --> Disable Hybrid Mode in DP PHY
    ScalerSetBit(P1D_27_KOFFSET_03, ~_BIT5, 0x00);
    ScalerSetBit(P7A_27_KOFFSET_03, ~_BIT5, 0x00);

    // [6] reg_Hybrid = 1'b0 --> Disable Hybrid Mode in HDMI PHY
    ScalerSetBit(P7B_28_KOFFSET_04, ~_BIT6, 0x00);
    ScalerSetBit(P7C_28_KOFFSET_04, ~_BIT6, 0x00);
    ScalerSetBit(P7D_28_KOFFSET_04, ~_BIT6, 0x00);
    ScalerSetBit(P7E_28_KOFFSET_04, ~_BIT6, 0x00);

    // [3] EN_ENHANCE_BIAS = 1 --> Enhance Clock Lane Input Buffer Bias Current
    // [2] PSM = 1'b1 --> Enable HDMI Clock Switch
#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
    // [2] PSM = 0 for DP
    ScalerSetBit(P1D_17_BANDGAP_03, ~(_BIT3 | _BIT2), _BIT3);
#else
    ScalerSetBit(P1D_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
    // [2] PSM = 0 for DP
    ScalerSetBit(P7A_17_BANDGAP_03, ~(_BIT3 | _BIT2), _BIT3);
#else
    ScalerSetBit(P7A_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
#endif

    ScalerSetBit(P7B_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P7C_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P7D_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    ScalerSetBit(P7E_17_BANDGAP_03, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));

    // [2] HST_BUF_SEL = 1'b0 --> Disable Hysteresis Amplifier in Clock Lane
    ScalerSetBit(P1D_1B_CMU_01, ~_BIT2, 0x00);
    ScalerSetBit(P7A_1B_CMU_01, ~_BIT2, 0x00);

    if(bSelect == _ON)
    {
        ////////////////
        // BangGap EN //
        ////////////////

        // [7] EN_GDI_BG = 1'b1 --> GDI BG Power On
        // [6:5] RBG = 2'b00 --> BG = 1.245V
        ScalerSetBit(P1D_14_BANDGAP_00, ~(_BIT6 | _BIT5), 0x00);
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT7, _BIT7);

        // HDMI Clock Gating to Measure Block
        ScalerSetBit(P71_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);
        ScalerSetBit(P72_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);
        ScalerSetBit(P73_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);
        ScalerSetBit(P74_E1_AUX_PS_REPLY, ~_BIT7, _BIT7);

#if(_MULTI_DISPLAY_MAX > 0x01)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // D0 [7:4] rx_en, [3:0] CDR_en always on
        ScalerSetByte(P1D_1A_CMU_00, 0xFF);
        // ACDR_en always on
        ScalerSetBit(P1D_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P1D_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // D1 [7:4] rx_en, [3:0] CDR_en always on
        ScalerSetByte(P7A_1A_CMU_00, 0xFF);
        // ACDR_en always on
        ScalerSetBit(P7A_2A_KOFFSET_06, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P7A_2B_KOFFSET_07, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif

#endif
        //////////////
        // Z0 AutoK //
        //////////////

        // [5] ibhx_ref_sel = 0 --> Vref = VBG
        ScalerSetBit(P1D_15_BANDGAP_01, ~_BIT5, 0x00);

        // [1] Z0_AUTOK = 1 --> Z0 Auto K
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT1, _BIT1);

        // [0] Z0_rstb = 1 -> 0 -> 1 --> 50ohm Auto Calibration
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT0, _BIT0);
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT0, 0x00);
        ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT0, _BIT0);

        // Waiting for Calibration
        for(ucTemp = 0; ucTemp <= 10; ucTemp++)
        {
            Delay5us(g_ucDelay5usN);
        }

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

        // Set 1k Manual Code
        ScalerSetByte(P27_A2_CBUS_RES_AUTOK_0, _MHL_1K);

        // Set 100k Manual Code
        ScalerSetByte(P27_A3_CBUS_RES_AUTOK_1, _MHL_100K);

#endif

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
        // Set 1k Manual Code
        ScalerSetByte(P67_A2_CBUS_RES_AUTOK_0, _MHL_1K);

        // Set 100k Manual Code
        ScalerSetByte(P67_A3_CBUS_RES_AUTOK_1, _MHL_100K);
#endif

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

        // Set 1k Manual Code
        ScalerSetByte(P1E_A2_CBUS_RES_AUTOK_0, _MHL_1K);

        // Set 100k Manual Code
        ScalerSetByte(P1E_A3_CBUS_RES_AUTOK_1, _MHL_100K);
#endif

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
        // Set 1k Manual Code
        ScalerSetByte(P5E_A2_CBUS_RES_AUTOK_0, _MHL_1K);

        // Set 100k Manual Code
        ScalerSetByte(P5E_A3_CBUS_RES_AUTOK_1, _MHL_100K);
#endif
    }
    else
    {
#if(_MULTI_DISPLAY_MAX > 0x01)

#if(_D0_INPUT_PORT_TYPE == _D0_DP_PORT)
        // D0 [7:4] rx_en, [3:0] CDR_en always off
        ScalerSetByte(P1D_1A_CMU_00, 0x00);
#endif

#if(_D1_INPUT_PORT_TYPE == _D1_DP_PORT)
        // D1 [7:4] rx_en, [3:0] CDR_en always off
        ScalerSetByte(P7A_1A_CMU_00, 0x00);
#endif

#endif

#if(_MHL_SUPPORT == _ON)
        // Check All CBUS Mac are not in Active State
        if((ScalerGetBit(P2A_A4_CBUS_CTRL_04, _BIT0) == 0x00) && (ScalerGetBit(P68_A4_CBUS_CTRL_04, _BIT0) == 0x00) &&
           (ScalerGetBit(P69_A4_CBUS_CTRL_04, _BIT0) == 0x00) && (ScalerGetBit(P6A_A4_CBUS_CTRL_04, _BIT0) == 0x00))
#endif
        {
            // [7] EN_GDI_BG = 1'b0 --> GDI BG Power Off
            ScalerSetBit(P1D_14_BANDGAP_00, ~_BIT7, 0x00);
        }
    }
}

#if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D0/D0 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx0Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D0();

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        SET_DIGITAL_PORT_SWITCH_TO_D6();
#endif
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D0();

#if((_D6_INPUT_PORT_TYPE == _D6_DP_PORT) && (_D6_INPUT_PORT_SWITCH_FROM == _SWITCH_FROM_D0))
        CLR_DIGITAL_PORT_SWITCH_TO_D6();
#endif
    }

    if(bSelect == _ON)
    {
        // [1] MHL_Mode = 1'b0 --> Disable MHL Mode
        ScalerSetBit(P1D_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] MHL_OP = 1'b0 --> Disable MHL OP
        ScalerSetBit(P1D_1B_CMU_01, ~_BIT4, 0x00);

        if(ScalerGetBit(P1D_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
#if(_D0_TMDS_SUPPORT == _ON)

            SET_TMDS_RX0_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P2_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX0_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT2;
            MCU_FFE4_DDC0_EDID_IRQ |= _BIT3;

#endif // End of #if(_D0_TMDS_SUPPORT == _ON)

            // Enable Z0
            ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        }
    }
    else
    {
#if(_D0_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D0_INPUT_PORT_TYPE == _D0_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        // ScalerTMDSRx0Hdcp2ResetProc();
#endif
    }
}


//--------------------------------------------------
// Description  : GDI Rx0 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx0PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx0Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P1D_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            ScalerGDIPhyRx0Z0Switch(_D0_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D0_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx0PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            ScalerGDIPhyRx0Z0Switch(_D0_INPUT_PORT, _OFF);

#if((_D0_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX0_TOGGLE_Z0();
            CLR_TMDS_RX0_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx0Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P1D_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P1D_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [3] Z0_manual = 1 --> Port0 50ohm Auto Mode
            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P1D_19_IMPEDANCE_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P1D_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P1D_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P1D_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P1D_11_DATA_TIMER, ~_BIT1, _BIT1);

            // [0] Analog Select to DP
            ScalerSetBit(P1D_17_BANDGAP_03, ~_BIT0, _BIT0);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_MULTI_DISPLAY_MAX == 0x01)
            // Disable RX_EN, Disable CDR_EN
            ScalerSetByte(P1D_1A_CMU_00, 0x00);
#endif
            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P1D_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D0_INPUT_PORT_TYPE == _D0_MHL_PORT)
            if(GET_D0_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P1D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_MULTI_DISPLAY_MAX == 0x01)
            // Disable RX_EN, Disable CDR_EN
            ScalerSetByte(P1D_1A_CMU_00, 0x00);
#endif
            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P1D_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

            break;

        default:

            break;
    }
}
#endif // End of #if(_D0_INPUT_PORT_TYPE != _D0_NO_PORT)

#if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D1/D1 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D1();
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D1();
    }

    if(bSelect == _ON)
    {
        // [1] MHL_Mode = 1'b0 --> Disable MHL Mode
        ScalerSetBit(P7A_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] MHL_OP = 1'b0 --> Disable MHL OP
        ScalerSetBit(P7A_1B_CMU_01, ~_BIT4, 0x00);

        if(ScalerGetBit(P7A_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
#if(_D1_TMDS_SUPPORT == _ON)

            SET_TMDS_RX1_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P70_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX1_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT2;
            MCU_FFE5_DDC1_EDID_IRQ |= _BIT3;

#endif // End of #if(_D1_TMDS_SUPPORT == _ON)

            // Enable Z0
            ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
        }
    }
    else
    {
#if(_D1_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FFE5_DDC1_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D1_INPUT_PORT_TYPE == _D1_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        // ScalerTMDSRx1Hdcp2ResetProc();
#endif
    }
}


//--------------------------------------------------
// Description  : GDI Rx1 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx1Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7A_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

            ScalerGDIPhyRx1Z0Switch(_D1_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D1_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx1PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            ScalerGDIPhyRx1Z0Switch(_D1_INPUT_PORT, _OFF);

#if((_D1_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX1_TOGGLE_Z0();
            CLR_TMDS_RX1_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx1Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P7A_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P7A_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [3] Z0_manual = 1 --> Port0 50ohm Auto Mode
            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P7A_19_IMPEDANCE_01, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            // [3:0] Z0_ADJR = 8 --> Z0 Differential Impedance = level 8
            ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P7A_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P7A_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P7A_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P7A_11_DATA_TIMER, ~_BIT1, _BIT1);

            // [0] Analog Select to DP
            ScalerSetBit(P7A_17_BANDGAP_03, ~_BIT0, _BIT0);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_MULTI_DISPLAY_MAX == 0x01)
            // Disable RX_EN, Disable CDR_EN
            ScalerSetByte(P7A_1A_CMU_00, 0x00);
#endif
            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7A_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D1_INPUT_PORT_TYPE == _D1_MHL_PORT)
            if(GET_D1_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P7A_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_MULTI_DISPLAY_MAX == 0x01)
            // Disable RX_EN, Disable CDR_EN
            ScalerSetByte(P7A_1A_CMU_00, 0x00);
#endif
            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7A_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);

            break;

        default:

            break;
    }
}
#endif // End of #if(_D1_INPUT_PORT_TYPE != _D1_NO_PORT)

#if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D2/D2 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D2();
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D2();
    }

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(GET_D2_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(bSelect == _ON)
        {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
            // Enable Z0
            ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif
        }
        else
        {
            if((ScalerGetBit(P7B_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX2_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE))
            {
                if((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                {
                    SET_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE();
                }
                else
                {
                    // Reset D2 CBUS While Non-NoteII
                    ScalerMHLRx2CBUSResetProc();
                }
            }
        }
    }
    else
    {
        ScalerMHLRx2CBUSPhySwitch(_OFF);

        if(bSelect == _ON)
        {
            if(ScalerGetBit(P7B_18_IMPEDANCE_00, _BIT7) == 0x00)
            {
                SET_TMDS_RX2_Z0_ASSERTED();

                // Clear HDCP Flag
                ScalerSetBit(P71_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

                // Initialize DDC Detection Process
                CLR_TMDS_RX2_DDC_DETECTED();

                // Enable DDC Toggle IRQ
                MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
                MCU_FE69_DDC2_EDID_IRQ |= _BIT3;

                // Enable Z0
                ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // Disable DDC Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);

            // Disable Z0
            ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Hdcp2 Proc
            ScalerTMDSRx2Hdcp2ResetProc();
#endif
        }
    }

#else // Else of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)

    if(bSelect == _ON)
    {
        // [1] Disable MHL Mode
        ScalerSetBit(P7B_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] Disable MHL OP
        ScalerSetBit(P7B_1B_CMU_01, ~_BIT4, 0x00);

#if(_D2_TMDS_SUPPORT == _ON)
        if(ScalerGetBit(P7B_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
            SET_TMDS_RX2_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P71_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX2_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FE69_DDC2_EDID_IRQ |= _BIT2;
            MCU_FE69_DDC2_EDID_IRQ |= _BIT3;
        }
#endif // End of #if(_D2_TMDS_SUPPORT == _ON)

        // Enable Z0
        ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }
    else
    {
#if(_D2_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FE69_DDC2_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D2_INPUT_PORT_TYPE == _D2_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        ScalerTMDSRx2Hdcp2ResetProc();
#endif
    }
#endif // End of #if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
}


//--------------------------------------------------
// Description  : GDI Rx2 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx2Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7B_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
                if((GET_MHL_RX2_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                   (((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                    ((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                {
                    // Reset D2 CBUS
                    ScalerMHLRx2CBUSResetProc();
                }
#endif
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if((GET_D2_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_RX2_SWITCH_PORT_DISCOVERY_DONE() == _TRUE) &&
               (ScalerGetBit(P7B_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX2_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
               (((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX2_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX2_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
            {
                // Reset CBUS
                ScalerMHLRx2CBUSResetProc();
            }
#endif
            ScalerGDIPhyRx2Z0Switch(_D2_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D2_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx2PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_D2_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx2PowerOffProc();
#endif
            ScalerGDIPhyRx2Z0Switch(_D2_INPUT_PORT, _OFF);

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            // MHL Power Off Process
            ScalerMHLRx2PowerOffProc();
#endif

#if((_D2_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX2_TOGGLE_Z0();
            CLR_TMDS_RX2_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx2Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P7B_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P7B_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [0] Z0_manual = 1 --> Port2 50ohm Auto Mode
            ScalerSetBit(P7B_17_BANDGAP_03, ~_BIT0, _BIT0);

            // [3:0] Z0_ADJR = 9 --> Z0 Differential Impedance = level 9
            ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P7B_19_IMPEDANCE_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P7B_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [2:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(P7B_00_DIG_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P7B_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P7B_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P7B_11_DATA_TIMER, ~_BIT1, _BIT1);

            ////////////////////
            // HDMI Interface //
            ////////////////////

            // Digital PHY Lane Swap Setting
            ScalerSetByte(P7B_01_DIG_01, 0x24);

            // Digital PHY P/N Swap Setting
            ScalerSetBit(P7B_03_DIG_03, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(P7B_05_DIG_05, ~_BIT7, _BIT7);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7B_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D2_INPUT_PORT_TYPE == _D2_MHL_PORT)
            if(GET_D2_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P7B_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7B_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7B_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

            break;

        default:

            break;
    }
}
#endif // End of #if(_D2_INPUT_PORT_TYPE != _D2_NO_PORT)

#if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D3/D3 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D3();
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D3();
    }

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

    if(GET_D3_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(bSelect == _ON)
        {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
            // Enable Z0
            ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif
        }
        else
        {
            if((ScalerGetBit(P7C_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX3_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE))
            {
                if((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                {
                    SET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE();
                }
                else
                {
                    // Reset D3 CBUS While Non-NoteII
                    ScalerMHLRx3CBUSResetProc();
                }
            }
        }
    }
    else
    {
        ScalerMHLRx3CBUSPhySwitch(_OFF);

        if(bSelect == _ON)
        {
            if(ScalerGetBit(P7C_18_IMPEDANCE_00, _BIT7) == 0x00)
            {
                SET_TMDS_RX3_Z0_ASSERTED();

                // Clear HDCP Flag
                ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

                // Initialize DDC Detection Process
                CLR_TMDS_RX3_DDC_DETECTED();

                // Enable DDC Toggle IRQ
                MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
                MCU_FE72_DDC3_EDID_IRQ |= _BIT3;

                // Enable Z0
                ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // Disable DDC Toggle IRQ
            MCU_FE72_DDC3_EDID_IRQ &= ~(_BIT3 | _BIT1);

            // Disable Z0
            ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Hdcp2 Proc
            ScalerTMDSRx3Hdcp2ResetProc();
#endif
        }
    }

#else // Else of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)

    if(bSelect == _ON)
    {
        // [1] Disable MHL Mode
        ScalerSetBit(P7C_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] Disable MHL OP
        ScalerSetBit(P7C_1B_CMU_01, ~_BIT4, 0x00);

#if(_D3_TMDS_SUPPORT == _ON)
        if(ScalerGetBit(P7C_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
            SET_TMDS_RX3_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P72_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX3_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FE72_DDC3_EDID_IRQ |= _BIT2;
            MCU_FE72_DDC3_EDID_IRQ |= _BIT3;
        }
#endif // End of #if(_D3_TMDS_SUPPORT == _ON)

        // Enable Z0
        ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }
    else
    {
#if(_D3_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FE72_DDC3_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D3_INPUT_PORT_TYPE == _D3_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        ScalerTMDSRx3Hdcp2ResetProc();
#endif
    }
#endif // End of #if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
}


//--------------------------------------------------
// Description  : GDI Rx3 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx3Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7C_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
                if((GET_MHL_RX3_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                   (((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                    ((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                {
                    // Reset D3 CBUS
                    ScalerMHLRx3CBUSResetProc();
                }
#endif
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if((GET_D3_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_RX3_SWITCH_PORT_DISCOVERY_DONE() == _TRUE) &&
               (ScalerGetBit(P7C_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX3_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
               (((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX3_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX3_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
            {
                // Reset CBUS
                ScalerMHLRx3CBUSResetProc();
            }
#endif
            ScalerGDIPhyRx3Z0Switch(_D3_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D3_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx3PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_D3_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx3PowerOffProc();
#endif
            ScalerGDIPhyRx3Z0Switch(_D3_INPUT_PORT, _OFF);

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            // MHL Power Off Process
            ScalerMHLRx3PowerOffProc();
#endif

#if((_D3_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX3_TOGGLE_Z0();
            CLR_TMDS_RX3_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx3Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P7C_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P7C_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [0] Z0_manual = 1 --> Port2 50ohm Auto Mode
            ScalerSetBit(P7C_17_BANDGAP_03, ~_BIT0, _BIT0);

            // [3:0] Z0_ADJR = 9 --> Z0 Differential Impedance = level 9
            ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P7C_19_IMPEDANCE_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P7C_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [2:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(P7C_00_DIG_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P7C_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P7C_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P7C_11_DATA_TIMER, ~_BIT1, _BIT1);

            ////////////////////
            // HDMI Interface //
            ////////////////////

            // Digital PHY Lane Swap Setting
            ScalerSetByte(P7C_01_DIG_01, 0x24);

            // Digital PHY P/N Swap Setting
            ScalerSetBit(P7C_03_DIG_03, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(P7C_05_DIG_05, ~_BIT7, _BIT7);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7C_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D3_INPUT_PORT_TYPE == _D3_MHL_PORT)
            if(GET_D3_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P7C_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7C_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7C_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

            break;

        default:

            break;
    }
}
#endif // End of #if(_D3_INPUT_PORT_TYPE != _D3_NO_PORT)

#if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D4/D4 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx4Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D4();
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D4();
    }

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

    if(GET_D4_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(bSelect == _ON)
        {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
            // Enable Z0
            ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif
        }
        else
        {
            if((ScalerGetBit(P7D_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX4_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE))
            {
                if((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                {
                    SET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE();
                }
                else
                {
                    // Reset D4 CBUS While Non-NoteII
                    ScalerMHLRx4CBUSResetProc();
                }
            }
        }
    }
    else
    {
        ScalerMHLRx4CBUSPhySwitch(_OFF);

        if(bSelect == _ON)
        {
            if(ScalerGetBit(P7D_18_IMPEDANCE_00, _BIT7) == 0x00)
            {
                SET_TMDS_RX4_Z0_ASSERTED();

                // Clear HDCP Flag
                ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

                // Initialize DDC Detection Process
                CLR_TMDS_RX4_DDC_DETECTED();

                // Enable DDC Toggle IRQ
                MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
                MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;

                // Enable Z0
                ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // Disable DDC Toggle IRQ
            MCU_FE7B_DDC4_EDID_IRQ &= ~(_BIT3 | _BIT1);

            // Disable Z0
            ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Hdcp2 Proc
            ScalerTMDSRx4Hdcp2ResetProc();
#endif
        }
    }

#else // Else of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)

    if(bSelect == _ON)
    {
        // [1] Disable MHL Mode
        ScalerSetBit(P7D_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] Disable MHL OP
        ScalerSetBit(P7D_1B_CMU_01, ~_BIT4, 0x00);

#if(_D4_TMDS_SUPPORT == _ON)
        if(ScalerGetBit(P7D_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
            SET_TMDS_RX4_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P73_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX4_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FE7B_DDC4_EDID_IRQ |= _BIT2;
            MCU_FE7B_DDC4_EDID_IRQ |= _BIT3;

#if((_D5_TMDS_SUPPORT == _ON) && (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))

            SET_TMDS_RX5_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P74_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX5_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
            MCU_FE84_DDC5_EDID_IRQ |= _BIT3;

#endif // End of #if((_D5_TMDS_SUPPORT == _ON) && (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
        }
#endif // End of #if(_D4_TMDS_SUPPORT == _ON)

        // Enable Z0
        ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }
    else
    {
#if(_D4_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FFE4_DDC0_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D4_INPUT_PORT_TYPE == _D4_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        ScalerTMDSRx4Hdcp2ResetProc();
#endif
    }
#endif // End of #if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
}


//--------------------------------------------------
// Description  : GDI Rx4 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx4PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx4Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7D_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
                if((GET_MHL_RX4_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                   (((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                    ((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                {
                    // Reset D4 CBUS
                    ScalerMHLRx4CBUSResetProc();
                }
#endif
            }

            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if((GET_D4_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_RX4_SWITCH_PORT_DISCOVERY_DONE() == _TRUE) &&
               (ScalerGetBit(P7D_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX4_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
               (((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX4_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX4_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
            {
                // Reset CBUS
                ScalerMHLRx4CBUSResetProc();
            }
#endif
            ScalerGDIPhyRx4Z0Switch(_D4_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D4_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx4PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_D4_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx4PowerOffProc();
#endif
            ScalerGDIPhyRx4Z0Switch(_D4_INPUT_PORT, _OFF);

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            // MHL Power Off Process
            ScalerMHLRx4PowerOffProc();
#endif

#if((_D4_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX4_TOGGLE_Z0();
            CLR_TMDS_RX4_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx4Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P7D_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P7D_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [0] Z0_manual = 1 --> Port2 50ohm Auto Mode
            ScalerSetBit(P7D_17_BANDGAP_03, ~_BIT0, _BIT0);

            // [3:0] Z0_ADJR = 9 --> Z0 Differential Impedance = level 9
            ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P7D_19_IMPEDANCE_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P7D_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [2:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(P7D_00_DIG_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P7D_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P7D_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P7D_11_DATA_TIMER, ~_BIT1, _BIT1);

            ////////////////////
            // HDMI Interface //
            ////////////////////

            // Digital PHY Lane Swap Setting
            ScalerSetByte(P7D_01_DIG_01, 0x24);

            // Digital PHY P/N Swap Setting
            ScalerSetBit(P7D_03_DIG_03, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(P7D_05_DIG_05, ~_BIT7, _BIT7);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7D_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D4_INPUT_PORT_TYPE == _D4_MHL_PORT)
            if(GET_D4_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P7D_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7D_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7D_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

            break;

        default:

            break;
    }
}
#endif // End of #if(_D4_INPUT_PORT_TYPE != _D4_NO_PORT)

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))
//--------------------------------------------------
// Description  : GDI Z0 Switch
// Input Value  : D5/D1 Port ; Z0 ON/OFF
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx5Z0Switch(BYTE ucPortSelect, bit bSelect)
{
    ucPortSelect = ucPortSelect;

    if(bSelect == _ON)
    {
        SET_DIGITAL_PORT_SWITCH_TO_D5();
    }
    else
    {
        CLR_DIGITAL_PORT_SWITCH_TO_D5();
    }

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(GET_D5_TMDS_MODE() == _TMDS_MHL_MODE)
    {
        if(bSelect == _ON)
        {
#if(_MHL_DEBUG_WITHOUT_CBUS_MODE == _ON)
            // Enable Z0
            ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
#endif
        }
        else
        {
            if((ScalerGetBit(P7E_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX5_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE))
            {
                if((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))
                {
                    SET_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE();
                }
                else
                {
                    // Reset D5 CBUS While Non-NoteII
                    ScalerMHLRx5CBUSResetProc();
                }
            }
        }
    }
    else
    {
        ScalerMHLRx5CBUSPhySwitch(_OFF);

        if(bSelect == _ON)
        {
            if(ScalerGetBit(P7E_18_IMPEDANCE_00, _BIT7) == 0x00)
            {
                SET_TMDS_RX5_Z0_ASSERTED();

                // Clear HDCP Flag
                ScalerSetBit(P74_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

                // Initialize DDC Detection Process
                CLR_TMDS_RX5_DDC_DETECTED();

                // Enable DDC Toggle IRQ
                MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
                MCU_FE84_DDC5_EDID_IRQ |= _BIT3;

                // Enable Z0
                ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
            }
        }
        else
        {
            // Disable DDC Toggle IRQ
            MCU_FE84_DDC5_EDID_IRQ &= ~(_BIT3 | _BIT1);

            // Disable Z0
            ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if(_TMDS_HDCP_2_2_SUPPORT == _ON)
            // Reset Hdcp2 Proc
            ScalerTMDSRx5Hdcp2ResetProc();
#endif
        }
    }

#else // Else of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)

    if(bSelect == _ON)
    {
        // [1] Disable MHL Mode
        ScalerSetBit(P7E_17_BANDGAP_03, ~_BIT1, 0x00);

        // [4] Disable MHL OP
        ScalerSetBit(P7E_1B_CMU_01, ~_BIT4, 0x00);

#if((_D5_TMDS_SUPPORT == _ON) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))
        if(ScalerGetBit(P7E_18_IMPEDANCE_00, _BIT7) == 0x00)
        {
            SET_TMDS_RX5_Z0_ASSERTED();

            // Clear HDCP Flag
            ScalerSetBit(P74_A9_TMDS_ABC0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

            // Initialize DDC Detection Process
            CLR_TMDS_RX5_DDC_DETECTED();

            // Enable DDC Toggle IRQ
            MCU_FE84_DDC5_EDID_IRQ |= _BIT2;
            MCU_FE84_DDC5_EDID_IRQ |= _BIT3;
        }
#endif // End of #if((_D5_TMDS_SUPPORT == _ON) && (_D4_INPUT_PORT_TYPE != _D4_DUAL_DVI_PORT))

        // Enable Z0
        ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));
    }
    else
    {
#if(_D5_TMDS_SUPPORT == _ON)

        // Disable DDC Toggle IRQ
        MCU_FE84_DDC5_EDID_IRQ &= ~(_BIT3 | _BIT1);
#endif
        // Disable Z0
        ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);

#if((_D5_INPUT_PORT_TYPE == _D5_HDMI_PORT) && (_TMDS_HDCP_2_2_SUPPORT == _ON))
        // Reset Hdcp2 Proc
        ScalerTMDSRx5Hdcp2ResetProc();
#endif
    }
#endif // End of #if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
}


//--------------------------------------------------
// Description  : GDI Rx5 Power Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx5PowerProc(EnumPowerAction enumPowerAction)
{
    ScalerGDIPhyRx5Power(enumPowerAction);

    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:

            break;

        case _POWER_ACTION_PS_TO_NORMAL:

            if(ScalerGetBit(P7E_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
                if((GET_MHL_RX5_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
                   (((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _CHROMA_MHL_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _CHROMA_MHL_ADOPTER_ID_LBYTE)) ||
                    ((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
                {
                    // Reset D5 CBUS
                    ScalerMHLRx5CBUSResetProc();
                }
#endif
            }

#if(_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT)

            if(ScalerGetBit(P7D_18_IMPEDANCE_00, _BIT7) == _BIT7)
            {
                // Enable RGB Z0
                ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), (_BIT6 | _BIT5 | _BIT4));
            }
#endif
            break;

        case _POWER_ACTION_OFF_TO_NORMAL:

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if((GET_D5_TMDS_MODE() == _TMDS_MHL_MODE) && (GET_MHL_RX5_SWITCH_PORT_DISCOVERY_DONE() == _TRUE) &&
               (ScalerGetBit(P7E_18_IMPEDANCE_00, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) == (_BIT7 | _BIT6 | _BIT5 | _BIT4)) &&
               (GET_MHL_RX5_PROCESS_STATE() >= _MHL_STATE_SET_DEV_CAP_DONE) &&
               (((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _HTC_BUTTERFLY_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _HUAWEI_D2_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _HUAWEI_D2_ADOPTER_ID_LBYTE)) ||
                ((GET_MHL_RX5_ADOPTER_ID_HBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_HBYTE) && (GET_MHL_RX5_ADOPTER_ID_LBYTE() == _SAMSUNG_NOTE2_ADOPTER_ID_LBYTE))))
            {
                // Reset CBUS
                ScalerMHLRx5CBUSResetProc();
            }
#endif
            ScalerGDIPhyRx5Z0Switch(_D5_INPUT_PORT, _ON);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

#if(_D5_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx5PowerSavingProc();
#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_FAKE_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

#if(_D5_TMDS_SUPPORT == _ON)
            // TMDS Power Off Process
            ScalerTMDSRx5PowerOffProc();
#endif
            ScalerGDIPhyRx5Z0Switch(_D5_INPUT_PORT, _OFF);

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            // MHL Power Off Process
            ScalerMHLRx5PowerOffProc();
#endif

#if((_D5_TMDS_SUPPORT == _ON) && (_TMDS_TOGGLE_HPD_Z0_FOR_ACER == _ON))
            CLR_TMDS_RX5_TOGGLE_Z0();
            CLR_TMDS_RX5_TOGGLE_Z0_EVENT();
#endif
            break;

        default:

            break;
    }
}


//--------------------------------------------------
// Description  : GDI Bandgap Power On/Off
// Input Value  : On/Off
// Output Value : None
//--------------------------------------------------
void ScalerGDIPhyRx5Power(EnumPowerAction enumPowerAction)
{
    switch(enumPowerAction)
    {
        case _POWER_ACTION_AC_ON_TO_NORMAL:
        case _POWER_ACTION_OFF_TO_NORMAL:
        case _POWER_ACTION_PS_TO_NORMAL:

            ////////////////////////
            // Clock Lane Enhance //
            ////////////////////////

            // [5:4] reg_rxvcom_sel = 2'b01 --> VDD - 0.3V
            ScalerSetBit(P7E_17_BANDGAP_03, ~(_BIT5 | _BIT4), _BIT4);


            ////////////////////////
            // Offset Calibration //
            ////////////////////////

            // [7] EN_BACK_OFFSET = 1'b1 --> Enable Background Offset Calibration
            // [6] EN_FORE_OFFSET = 1'b0 --> Disable Auto K-offset
            // [5] FORE_OFF_AUTOK = 1'b0 --> Disable Auto K-offset Auto Mode
            ScalerSetBit(P7E_24_KOFFSET_00, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);


            //////////////
            // Z0 AutoK //
            //////////////

            // [0] Z0_manual = 1 --> Port2 50ohm Auto Mode
            ScalerSetBit(P7E_17_BANDGAP_03, ~_BIT0, _BIT0);

            // [3:0] Z0_ADJR = 9 --> Z0 Differential Impedance = level 9
            ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            // [2:0] Z0_CM_ADJR = 6 --> Z0 Common Mode Impedance = level 6
            ScalerSetBit(P7E_19_IMPEDANCE_01, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            // [7] p_channel_en = 1 --> Switch p Channel 50ohm Z0
            // [6] n_channel_en = 1 --> Switch n Channel 50ohm Z0
            ScalerSetBit(P7E_17_BANDGAP_03, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));


            ///////////////
            // Reset PHY //
            ///////////////

            // [2:0] phy_si_reset_n = 4'b1111 --> Normal Digital PHY
            ScalerSetBit(P7E_00_DIG_00, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            // [1] bypass_clk_rdy = 1 --> Manual Mode
            ScalerSetBit(P7E_0E_SDM_03, ~_BIT1, _BIT1);

            // [1] bypass_eqen_rdy = 1 --> Manual Mode
            ScalerSetBit(P7E_10_EQEN_TIMER, ~_BIT1, _BIT1);

            // [1] bypass_data_rdy = 1 --> Manual Mode
            ScalerSetBit(P7E_11_DATA_TIMER, ~_BIT1, _BIT1);

            ////////////////////
            // HDMI Interface //
            ////////////////////

            // Digital PHY Lane Swap Setting
            ScalerSetByte(P7E_01_DIG_01, 0x24);

            // Digital PHY P/N Swap Setting
            ScalerSetBit(P7E_03_DIG_03, ~(_BIT6 | _BIT5 | _BIT4), 0x00);

            // Digital PHY Select to HDMI
            ScalerSetBit(P7E_05_DIG_05, ~_BIT7, _BIT7);

            break;

        case _POWER_ACTION_NORMAL_TO_PS:
        case _POWER_ACTION_NOSUPPORT_PS_TO_PS:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7E_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

#if(_TMDS_Z0_POWER_SAVING_OPTION == _ONLY_CLK_CHANNEL_CONNECTED_FOR_PS)

#if(_D5_INPUT_PORT_TYPE == _D5_MHL_PORT)
            if(GET_D5_TMDS_MODE() == _TMDS_HDMI_MODE)
            {
                // Disable RGB Z0
                ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
            }
#else
            // Disable RGB Z0
            ScalerSetBit(P7E_18_IMPEDANCE_00, ~(_BIT6 | _BIT5 | _BIT4), 0x00);
#endif

#endif
            break;

        case _POWER_ACTION_NORMAL_TO_OFF:
        case _POWER_ACTION_AC_ON_TO_OFF:
        case _POWER_ACTION_NOSUPPORT_PS_TO_OFF:
        case _POWER_ACTION_PS_TO_OFF:

            // Disable R/G/B RX_EN, Disable R/G/B/Clock CDR_EN
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT7, _BIT7);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT6, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT5, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT4, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT3, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT2, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT1, 0x00);
            Delay5us(g_ucDelay5usN);
            ScalerSetBit(P7E_1A_CMU_00, ~_BIT0, 0x00);

            // Disable Auto k-offset(foreground)
            // Disable Auto k-offset auto mode (foreground)
            ScalerSetBit(P7E_24_KOFFSET_00, ~(_BIT6 | _BIT5), 0x00);

            break;

        default:

            break;
    }
}
#endif // End of #if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) || (_D4_INPUT_PORT_TYPE == _D4_DUAL_DVI_PORT))


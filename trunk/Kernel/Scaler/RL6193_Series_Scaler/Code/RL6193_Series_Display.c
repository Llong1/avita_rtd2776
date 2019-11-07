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
// ID Code      : RL6193_Series_Display.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

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
#if(_PANEL_STYLE == _PANEL_LVDS)
void ScalerDisplayLvdsInitialTable(void);
void ScalerDisplayLvdsPower(bit bOn);
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv);
void ScalerDisplayLvdsPhaseConrol(void);
void ScalerDisplayLvdsSlewRateConrol(void);

void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand);
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand);
bit ScalerDisplayGetLvdsPowerStatus(void);
void ScalerDisplayLvdsPLL(bit bOn);

#elif(_PANEL_STYLE == _PANEL_VBO)
void ScalerDisplayVboDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane);
void ScalerDisplayVboInitialTable(void);
bit ScalerDisplayGetVboPowerStatus(void);
void ScalerDisplayVboPLL(bit bOn);
void ScalerDisplaySetVboPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
void ScalerDisplayVboPower(bit bOn);
void ScalerDisplayVboSetZ0(void);
#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Initial Settings for Display Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsInitialTable(void)
{
    // Set DISP mode is LVDS
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), _BIT0); // lvds mode

    // Set Panel Display Type
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT0), ((_LVDS_OUTPUT_PORT << 6) | (_LVDS_PANEL_SECTION << 4) | (_LVDS_TABLE_TYPE << 0))); // setup lvds output port

    // Display Resolution Control Settings
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~(_BIT2 | _BIT1), (_PANEL_DISP_BIT_MODE << 1)); // 18/24/30 bit

    // Dispaly Panel Resoultion
    ScalerSetBit(P39_01_LVDS_DISPLAY_CONV_CTRL0, ~_BIT3, ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_30_BIT) ? _BIT3 : 0x00));// 18/24/30 bit

    // Set LVDS Interface Type
    ScalerSetByte(P39_06_LVDS_DISPLAY_CONV_CTRL5, ((_LVDS_RB_SWAP << 7) | (_LVDS_ML_SWAP << 6) | (_LVDS_PN_SWAP << 4) | (_BIT3) | (_LVDS_CLK_CHANNEL_SEL << 1) | (_LVDS_PAIR_MIRROR << 0)));

    // Set LVDS Display Content
    ScalerSetBit(P39_07_LVDS_DISPLAY_CONV_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_DVS_INVERT << 3) | (_LVDS_DHS_INVERT << 2) | (_LVDS_DEN_INVERT << 1) | (_BIT0)));

    // Set OCLK: Non-inverted
    ScalerSetDataPortBit(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_20_DISPLAY_CLOCK_FINE_TUNE, ~_BIT0, 0x00);

    // Set LVDS BW Parameter
    ScalerSetByte(P15_0D_LVDS_COMMON_AB_CTRL13, 0xAB);
    ScalerSetByte(P55_0D_LVDS_COMMON_AB_CTRL13, 0xAB);
    ScalerSetByte(P95_0D_LVDS_COMMON_AB_CTRL13, 0xAB);
    ScalerSetByte(PD5_0D_LVDS_COMMON_AB_CTRL13, 0xAB);

    // Set LVDS common mode Voltage
#if(_LVDS_VCM_CONTROL == _LVDS_VCM_LOW)

    ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
    ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
    ScalerSetBit(P95_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));
    ScalerSetBit(PD5_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5));

#elif(_LVDS_VCM_CONTROL == _LVDS_VCM_NORMAL)

    ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P95_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT3 | _BIT1 | _BIT0));

#elif(_LVDS_VCM_CONTROL == _LVDS_VCM_HIGH)

    ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_LVDS_VCM_CONTROL == _LVDS_VCM_USER)

    ScalerSetBit(P15_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));
    ScalerSetBit(P55_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));
    ScalerSetBit(P95_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));
    ScalerSetBit(PD5_01_LVDS_COMMON_AB_CTRL1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | (_LVDS_VCM_USER_LEVEL & 0x1F)));

#endif // #if(_LVDS_VCM_CONTROL == _LVDS_VCM_LOW)

    // Set LVDS Driving Double Current Disable
    ScalerSetBit(P15_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_20_LVDS_PORTA_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_30_LVDS_PORTB_CTRL0, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Set LVDS Driving Control
    ScalerDisplayLvdsDrivingControl(_LVDS_DRIV_CONTROL);

    // Set LVDS Phase Selection
    ScalerDisplayLvdsPhaseConrol();

    // Set LVDS data slew rate control
    ScalerDisplayLvdsSlewRateConrol();

    // Set LVDS TX output Data selection: Data / Strongly pull down / Termination
    ScalerDisplayLvdsTxDataSel(); // ----------------root cause

    // Set LVDS TX Output Data Swap Selection
    ScalerDisplayLvdsTxPortSwap();

    // Disable LVDS CLK Signal, and Set To DC Level
    ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);

    // Set LVDS Shape-adjustment
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P95_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(P95_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_23_LVDS_PORTA_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_33_LVDS_PORTB_CTRL3, ~(_BIT4 | _BIT3 | _BIT1 | _BIT0), (_BIT4 | _BIT3 | _BIT1 | _BIT0));

    // Set LVDS Pre-emphasis On
    ScalerSetBit(P15_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P15_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P55_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P55_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P95_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(P95_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(PD5_23_LVDS_PORTA_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
    ScalerSetBit(PD5_33_LVDS_PORTB_CTRL3, ~(_BIT5 | _BIT2), (_BIT5 | _BIT2));
}

//--------------------------------------------------
// Description  : LVDS Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPower(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_E)

        // Disable Port EF Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port EF LVDS Block
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_F)

        // Disable Port EF Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port EF LVDS Block
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6));


#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Disable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port AB LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Disable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port CD LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_EF)

        // Disable Port EF Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port EF LVDS Block
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

        // Disable Port GH Weakly and Strongly Pull Down
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port GH LVDS Block
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Disable Port ABCD Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port ABCD LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

        // Disable Port CDEF Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port CDEF LVDS Block
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

        // Disable Port EFGH Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port EFGH LVDS Block
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

        // Disable Port ABCDEFGH Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), 0x00);
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), 0x00);

        // Power Up Port ABCDEFGH LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), (_BIT7 | _BIT6 | _BIT5));

#endif // #if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)
    }

    else
    {
#if(_LVDS_PORT_SEL == _LVDS_1_PORT_E)

        // Enable Port EF Weakly and Strongly Pull Down
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
   

#elif(_LVDS_PORT_SEL == _LVDS_1_PORT_F)

        // Enable Port B Weakly and Strongly Pull Down (Analog Port A)
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

        // Power Down Port AB LVDS Block
       // ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Enable Port AB Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Enable Port CD Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_EF)

        // Enable Port EF Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

        // Enable Port GH Weakly and Strongly Pull Down
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Enable Port ABCD Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

        // Enable Port CDEF Weakly and Strongly Pull Down
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

        // Enable Port EFGH Weakly and Strongly Pull Down
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

        // Enable Port ABCDEFGH Weakly and Strongly Pull Down
        ScalerSetBit(P15_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P15_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P55_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(P95_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PD5_26_LVDS_PORTA_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        ScalerSetBit(PD5_36_LVDS_PORTB_CTRL6, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));

#endif  // #if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Power Down Port ABCDEFGH LVDS Block
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
    }
}

//--------------------------------------------------
// Description  : Set LVDS driving control
// Input Value  : Driving current for Data and Clock pair
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsDrivingControl(BYTE ucDriv)
{
#if(_LVDS_TERMINATION_CONTROL == _ENABLE)

    // Set LVDS Output Termination 50ohm
    ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0xFF);
    ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0xFF);
    ScalerSetByte(P95_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(P95_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(P95_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(P95_38_LVDS_PORTB_CTRL8, 0xFF);
    ScalerSetByte(PD5_27_LVDS_PORTA_CTRL7, 0xFF);
    ScalerSetByte(PD5_28_LVDS_PORTA_CTRL8, 0xFF);
    ScalerSetByte(PD5_37_LVDS_PORTB_CTRL7, 0xFF);
    ScalerSetByte(PD5_38_LVDS_PORTB_CTRL8, 0xFF);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            // Set LVDS Output Termination 70ohm
            ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x55);
            ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x55);
            ScalerSetByte(P95_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(P95_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(P95_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(P95_38_LVDS_PORTB_CTRL8, 0x55);
            ScalerSetByte(PD5_27_LVDS_PORTA_CTRL7, 0x55);
            ScalerSetByte(PD5_28_LVDS_PORTA_CTRL8, 0x55);
            ScalerSetByte(PD5_37_LVDS_PORTB_CTRL7, 0x55);
            ScalerSetByte(PD5_38_LVDS_PORTB_CTRL8, 0x55);

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT1);

            break;

        default:

            break;
    }

#else // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#elif(_LVDS_TERMINATION_CONTROL == _DISABLE)

    // Disable Output Termination
    ScalerSetByte(P15_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(P15_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P15_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P15_38_LVDS_PORTB_CTRL8, 0x00);
    ScalerSetByte(P55_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(P55_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P55_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P55_38_LVDS_PORTB_CTRL8, 0x00);
    ScalerSetByte(P95_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(P95_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(P95_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(P95_38_LVDS_PORTB_CTRL8, 0x00);
    ScalerSetByte(PD5_27_LVDS_PORTA_CTRL7, 0x00);
    ScalerSetByte(PD5_28_LVDS_PORTA_CTRL8, 0x00);
    ScalerSetByte(PD5_37_LVDS_PORTB_CTRL7, 0x00);
    ScalerSetByte(PD5_38_LVDS_PORTB_CTRL8, 0x00);

#if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_1)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_2)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT1));
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT5 | _BIT3 | _BIT1));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT0));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }

#elif(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_3)

    // Set LVDS Pre-emphasis
    ScalerSetBit(P15_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P95_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(PD5_29_LVDS_PORTA_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_2A_LVDS_PORTA_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_39_LVDS_PORTB_CTRL9, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_3A_LVDS_PORTB_CTRL10, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    switch(ucDriv)
    {
        case _LVDS_DRIV_CONTROL_2_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_2_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_3_0:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));

            break;

        case _LVDS_DRIV_CONTROL_3_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));

            break;

        case _LVDS_DRIV_CONTROL_1_5:

            ScalerSetBit(P15_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P55_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(P95_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetBit(PD5_02_LVDS_COMMON_AB_CTRL2, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        default:

            break;
    }
#endif // #if(_LVDS_PRE_EMPHASIS_CONTROL == _LVDS_PRE_EMPHASIS_0)

#endif // End of #if(_LVDS_TERMINATION_CONTROL == _ENABLE)
}

//--------------------------------------------------
// Description  : LVDS Phase Selection Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPhaseConrol(void)
{
    BYTE ucLvdsPhaseSeedH = 0x03;
    BYTE ucLvdsPhaseSeedL = 0x0F;
    BYTE ucLvdsPhaseH = 0x00;
    BYTE ucLvdsPhaseL = 0x00;

    ScalerSetBit(P15_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P15_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P55_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P55_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P95_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(P95_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(PD5_21_LVDS_PORTA_CTRL1, ~_BIT7, _BIT7);
    ScalerSetBit(PD5_31_LVDS_PORTB_CTRL1, ~_BIT7, _BIT7);

// PI_Phase_AB0 select
#if(_LVDS_PI_PHASE_AB0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB0_SEL >> 2));  // ((_LVDS_PI_PHASE_AB0_SEL - (_LVDS_PI_PHASE_AB0_SEL % 4)) >> 2)
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB0_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_AB1 select
#if(_LVDS_PI_PHASE_AB1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB1_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_AB2 select
#if(_LVDS_PI_PHASE_AB2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB2_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_AB3 select
#if(_LVDS_PI_PHASE_AB3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_AB3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_AB3_SEL % 8)) & 0xF0;

    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P15_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P15_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

// PI_Phase_CD0 select
#if(_LVDS_PI_PHASE_CD0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD0_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD0_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_CD1 select
#if(_LVDS_PI_PHASE_CD1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD1_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_CD2 select
#if(_LVDS_PI_PHASE_CD2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD2_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_CD3 select
#if(_LVDS_PI_PHASE_CD3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_CD3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_CD3_SEL % 8)) & 0xF0;

    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P55_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P55_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

// PI_Phase_EF0 select
#if(_LVDS_PI_PHASE_EF0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_EF0_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_EF0_SEL % 8)) & 0xF0;

    ScalerSetBit(P95_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P95_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P95_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P95_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_EF1 select
#if(_LVDS_PI_PHASE_EF1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_EF1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_EF1_SEL % 8)) & 0xF0;

    ScalerSetBit(P95_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P95_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P95_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P95_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_EF2 select
#if(_LVDS_PI_PHASE_EF2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_EF2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_EF2_SEL % 8)) & 0xF0;

    ScalerSetBit(P95_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P95_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P95_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P95_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_EF3 select
#if(_LVDS_PI_PHASE_EF3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_EF3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_EF3_SEL % 8)) & 0xF0;

    ScalerSetBit(P95_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(P95_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(P95_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(P95_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

// PI_Phase_GH0 select
#if(_LVDS_PI_PHASE_GH0_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_GH0_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_GH0_SEL % 8)) & 0xF0;

    ScalerSetBit(PD5_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(PD5_05_LVDS_COMMON_AB_CTRL5, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(PD5_04_LVDS_COMMON_AB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(PD5_05_LVDS_COMMON_AB_CTRL5, 0x30);
#endif

// PI_Phase_GH1 select
#if(_LVDS_PI_PHASE_GH1_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_GH1_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_GH1_SEL % 8)) & 0xF0;

    ScalerSetBit(PD5_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(PD5_07_LVDS_COMMON_AB_CTRL7, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(PD5_06_LVDS_COMMON_AB_CTRL6, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(PD5_07_LVDS_COMMON_AB_CTRL7, 0x30);
#endif

// PI_Phase_GH2 select
#if(_LVDS_PI_PHASE_GH2_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_GH2_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_GH2_SEL % 8)) & 0xF0;

    ScalerSetBit(PD5_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(PD5_09_LVDS_COMMON_AB_CTRL9, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(PD5_08_LVDS_COMMON_AB_CTRL8, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(PD5_09_LVDS_COMMON_AB_CTRL9, 0x30);
#endif

// PI_Phase_GH3 select
#if(_LVDS_PI_PHASE_GH3_SEL <= _LVDS_PHASE16)
    ucLvdsPhaseH = (ucLvdsPhaseSeedH << (_LVDS_PI_PHASE_GH3_SEL >> 2));
    ucLvdsPhaseL = (ucLvdsPhaseSeedL << (_LVDS_PI_PHASE_GH3_SEL % 8)) & 0xF0;

    ScalerSetBit(PD5_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((ucLvdsPhaseH >> 4) & 0x0F));
    ScalerSetByte(PD5_0B_LVDS_COMMON_AB_CTRL11, (((ucLvdsPhaseH << 4) & 0xF0) | ((ucLvdsPhaseL >> 4) & 0x0F)));
#else
    ScalerSetBit(PD5_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetByte(PD5_0B_LVDS_COMMON_AB_CTRL11, 0x30);
#endif

    // Set Port A Phase selection (Analog Port B)
    ScalerSetBit(P15_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_A0_PHASE << 2) | (_LVDS_A1_PHASE << 0)));
    ScalerSetByte(P15_35_LVDS_PORTB_CTRL5, ((_LVDS_A2_PHASE << 6) | (_LVDS_AC_PHASE << 4) | (_LVDS_A3_PHASE << 2) | (_LVDS_A4_PHASE << 0)));

    // Set Port B Phase selection (Analog Port A)
    ScalerSetBit(P15_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_B0_PHASE << 2) | (_LVDS_B1_PHASE << 0)));
    ScalerSetByte(P15_25_LVDS_PORTA_CTRL5, ((_LVDS_B2_PHASE << 6) | (_LVDS_BC_PHASE << 4) | (_LVDS_B3_PHASE << 2) | (_LVDS_B4_PHASE << 0)));

    // Set Port C Phase selection (Analog Port B)
    ScalerSetBit(P55_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_C0_PHASE << 2) | (_LVDS_C1_PHASE << 0)));
    ScalerSetByte(P55_35_LVDS_PORTB_CTRL5, ((_LVDS_C2_PHASE << 6) | (_LVDS_CC_PHASE << 4) | (_LVDS_C3_PHASE << 2) | (_LVDS_C4_PHASE << 0)));

    // Set Port D Phase selection (Analog Port A)
    ScalerSetBit(P55_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_D0_PHASE << 2) | (_LVDS_D1_PHASE << 0)));
    ScalerSetByte(P55_25_LVDS_PORTA_CTRL5, ((_LVDS_D2_PHASE << 6) | (_LVDS_DC_PHASE << 4) | (_LVDS_D3_PHASE << 2) | (_LVDS_D4_PHASE << 0)));

    // Set Port E Phase selection (Analog Port B)
    ScalerSetBit(P95_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_E0_PHASE << 2) | (_LVDS_E1_PHASE << 0)));
    ScalerSetByte(P95_35_LVDS_PORTB_CTRL5, ((_LVDS_E2_PHASE << 6) | (_LVDS_EC_PHASE << 4) | (_LVDS_E3_PHASE << 2) | (_LVDS_E4_PHASE << 0)));

    // Set Port F Phase selection (Analog Port A)
    ScalerSetBit(P95_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_F0_PHASE << 2) | (_LVDS_F1_PHASE << 0)));
    ScalerSetByte(P95_25_LVDS_PORTA_CTRL5, ((_LVDS_F2_PHASE << 6) | (_LVDS_FC_PHASE << 4) | (_LVDS_F3_PHASE << 2) | (_LVDS_F4_PHASE << 0)));

    // Set Port G Phase selection (Analog Port B)
    ScalerSetBit(PD5_34_LVDS_PORTB_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_G0_PHASE << 2) | (_LVDS_G1_PHASE << 0)));
    ScalerSetByte(PD5_35_LVDS_PORTB_CTRL5, ((_LVDS_G2_PHASE << 6) | (_LVDS_GC_PHASE << 4) | (_LVDS_G3_PHASE << 2) | (_LVDS_G4_PHASE << 0)));

    // Set Port H Phase selection (Analog Port A)
    ScalerSetBit(PD5_24_LVDS_PORTA_CTRL4, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((_LVDS_H0_PHASE << 2) | (_LVDS_H1_PHASE << 0)));
    ScalerSetByte(PD5_25_LVDS_PORTA_CTRL5, ((_LVDS_H2_PHASE << 6) | (_LVDS_HC_PHASE << 4) | (_LVDS_H3_PHASE << 2) | (_LVDS_H4_PHASE << 0)));

    // Set LVDS PI Control Enable, and Set LVDS ckpixel_inv Falling Edge
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(P95_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
    ScalerSetBit(PD5_03_LVDS_COMMON_AB_CTRL3, ~(_BIT4 | _BIT1 | _BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : LVDS Slew rate Contorl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSlewRateConrol(void)
{
#if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(P95_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(P95_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    ScalerSetBit(PD5_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
    ScalerSetBit(PD5_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_1)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

    ScalerSetBit(P95_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(P95_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

    ScalerSetBit(PD5_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));
    ScalerSetBit(PD5_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_2)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P95_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(PD5_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#elif(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_3)

    ScalerSetBit(P15_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P15_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P55_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P55_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(P95_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(P95_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

    ScalerSetBit(PD5_22_LVDS_PORTA_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
    ScalerSetBit(PD5_32_LVDS_PORTB_CTRL2, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

#endif // #if(_LVDS_SR_CONTROL == _LVDS_SR_CONTROL_0)
}

//--------------------------------------------------
// Description  : Manual set LVDS VCO band
// Input Value  : ucVcoBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetVcoBand(BYTE ucVcoBand)
{
    ScalerSetBit(P15_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
    ScalerSetBit(P55_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
    ScalerSetBit(P95_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
    ScalerSetBit(PD5_0E_LVDS_COMMON_AB_CTRL14, ~(_BIT1 | _BIT0), ucVcoBand);
}

//--------------------------------------------------
// Description  : Set LVDS PI Operation band
// Input Value  : ucPhaseBand
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsSetPhaseBand(BYTE ucPhaseBand)
{
    ScalerSetBit(P15_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P15_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P55_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P95_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P95_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P95_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P95_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(P95_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(PD5_03_LVDS_COMMON_AB_CTRL3, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(PD5_04_LVDS_COMMON_AB_CTRL4, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(PD5_06_LVDS_COMMON_AB_CTRL6, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(PD5_08_LVDS_COMMON_AB_CTRL8, ~(_BIT6 | _BIT5), ucPhaseBand);
    ScalerSetBit(PD5_0A_LVDS_COMMON_AB_CTRL10, ~(_BIT6 | _BIT5), ucPhaseBand);
}

//--------------------------------------------------
// Description  : Get LVDS Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetLvdsPowerStatus(void)
{
    return (bit)((ScalerGetBit(P15_00_LVDS_COMMON_AB_CTRL0, _BIT3)) |
                 (ScalerGetBit(P55_00_LVDS_COMMON_AB_CTRL0, _BIT3)) |
                 (ScalerGetBit(P95_00_LVDS_COMMON_AB_CTRL0, _BIT3)) |
                 (ScalerGetBit(PD5_00_LVDS_COMMON_AB_CTRL0, _BIT3)));
}

//--------------------------------------------------
// Description  : LVDS PLL(Data) Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayLvdsPLL(bit bOn)
{
    if(bOn == _ON)
    {
#if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Power Up LVDS Port AB PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_CD)

        // Power Up LVDS Port CD PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));


#elif((_LVDS_PORT_SEL == _LVDS_1_PORT_E) || (_LVDS_PORT_SEL == _LVDS_1_PORT_F) || (_LVDS_PORT_SEL == _LVDS_2_PORT_EF))

        // Power Up LVDS Port EF PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_2_PORT_GH)

        // Power Up LVDS Port GH PLL
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_ABCD)

        // Power Up LVDS Port ABCD PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_CDEF)

        // Power Up LVDS Port CDEF PLL
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_4_PORT_EFGH)

        // Power Up LVDS Port EFGH PLL
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#elif(_LVDS_PORT_SEL == _LVDS_8_PORT_ABCDEFGH)

        // Power Up LVDS Port ABCDEFGH PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT3));

#endif // #if(_LVDS_PORT_SEL == _LVDS_2_PORT_AB)

        // Wait for LVDS PLL stable
        ScalerTimerDelayXms(2);

        // Set LVDS CLK Signal
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0xE3);
    }

    else
    {
        // Power Down LVDS Port ABCDEFGH PLL
        ScalerSetBit(P15_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P55_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(P95_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));
        ScalerSetBit(PD5_00_LVDS_COMMON_AB_CTRL0, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2));

        // Disable LVDS CLK Signal, and Set To DC Level
        ScalerSetByte(P39_1D_LVDS_CLK_CTRL, 0x00);
    }
}

#elif(_PANEL_STYLE == _PANEL_VBO)
//--------------------------------------------------
// Description  : Setting for Vbyone driving control
// Input Value  : Driving current and Pre-emphasis for Vby1 Data Lane
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboDrivingControl(BYTE ucDrvLane, BYTE ucEmpLane)
{
    switch(ucDrvLane)
    {
        case _VBO_DRIV_CONTROL_2_0:

            ScalerSetByte(P38_A7_PHY0_APHY_07, 0x66);
            ScalerSetByte(P38_A8_PHY0_APHY_08, 0x66);
            ScalerSetByte(P38_A9_PHY0_APHY_09, 0x66);
            ScalerSetByte(P38_AA_PHY0_APHY_0A, 0x66);

            break;

        case _VBO_DRIV_CONTROL_2_5:

            ScalerSetByte(P38_A7_PHY0_APHY_07, 0x99);
            ScalerSetByte(P38_A8_PHY0_APHY_08, 0x99);
            ScalerSetByte(P38_A9_PHY0_APHY_09, 0x99);
            ScalerSetByte(P38_AA_PHY0_APHY_0A, 0x99);

            break;

        case _VBO_DRIV_CONTROL_3_0:

            ScalerSetByte(P38_A7_PHY0_APHY_07, 0xCC);
            ScalerSetByte(P38_A8_PHY0_APHY_08, 0xCC);
            ScalerSetByte(P38_A9_PHY0_APHY_09, 0xCC);
            ScalerSetByte(P38_AA_PHY0_APHY_0A, 0xCC);

            break;

        case _VBO_DRIV_CONTROL_3_5:

            ScalerSetByte(P38_A7_PHY0_APHY_07, 0xFF);
            ScalerSetByte(P38_A8_PHY0_APHY_08, 0xFF);
            ScalerSetByte(P38_A9_PHY0_APHY_09, 0xFF);
            ScalerSetByte(P38_AA_PHY0_APHY_0A, 0xFF);

            break;

        default:

            break;
    }

    switch(ucEmpLane)
    {
        case _VBO_PRE_EMPHASIS_0:

            // Pre-emphasis off
            ScalerSetBit(P38_A2_PHY0_APHY_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

            break;

        case _VBO_PRE_EMPHASIS_1:

            ScalerSetByte(P38_B1_PHY0_APHY_11, 0xFF);

            // Pre-emphasis on
            ScalerSetBit(P38_A2_PHY0_APHY_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _VBO_PRE_EMPHASIS_2:

            ScalerSetByte(P38_B1_PHY0_APHY_11, 0xFF);
            ScalerSetByte(P38_A3_PHY0_APHY_03, 0x90);
            ScalerSetByte(P38_A4_PHY0_APHY_04, 0x90);
            ScalerSetByte(P38_A5_PHY0_APHY_05, 0x90);
            ScalerSetByte(P38_A6_PHY0_APHY_06, 0x90);

            // Pre-emphasis on
            ScalerSetBit(P38_A2_PHY0_APHY_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        case _VBO_PRE_EMPHASIS_3:

            ScalerSetByte(P38_B1_PHY0_APHY_11, 0xFF);
            ScalerSetByte(P38_A3_PHY0_APHY_03, 0xFC);
            ScalerSetByte(P38_A4_PHY0_APHY_04, 0xFC);
            ScalerSetByte(P38_A5_PHY0_APHY_05, 0xFC);
            ScalerSetByte(P38_A6_PHY0_APHY_06, 0xFC);

            // Pre-emphasis on
            ScalerSetBit(P38_A2_PHY0_APHY_02, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));

            break;

        default:

            break;
    }
}
//--------------------------------------------------
// Description  : Initial Settings for Vbyone Interface
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboInitialTable(void)
{
    // Set DISP mode is Vby1
    ScalerSetBit(P39_00_LVDS_DISP_TYPE, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT0));

    // Set PLL input clk is Vby1
    ScalerSetBit(P38_17_CTS_FIFO_L, ~(_BIT7 | _BIT6 | _BIT5), ((_VBO_HS_CONTROL & _BIT0) << 7));

    // Set Vby1 Display Data Bit Resolution
    ScalerSetBit(P38_00_VIDEO_FORMAT_H, ~(_BIT5 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _VBO_BIT_MODE);

    // Set Vby1 Display Data Lane
    ScalerSetByte(P38_03_LANE_STATUS_H, (_BIT6 | _VBO_OUTPUT_PORT));

    // Set Vby1 Display Type
    ScalerSetByte(P38_04_LANE_STATUS_L, ((_VBO_PANEL_SECTION << 3) | _VBO_BYTE_MODE));

    // Set Vby1 MLSwap and LaneSwap Control
    ScalerSetBit(P38_27_VBY1_FW_CTRL, ~(_BIT5 | _BIT4), ((_VBO_ML_SWAP << 5) | (_VBO_LANE_SWAP << 4)));

    // Set Vby1 Transmit Control
    ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~(_BIT5 | _BIT4), (_BIT5 | (_VBO_VIDEO_TRANSFER_TYPE << 4)));
    ScalerSetBit(P38_0A_TRANSMIT_CONTROL_H1, ~_BIT6, 0x00);
    ScalerSetBit(P38_0D_TRANSMIT_STATUS, ~_BIT7, _BIT7);
    ScalerSetBit(P38_0E_THREE_FLAG, ~(_BIT2 | _BIT1 | _BIT0), ((_VBO_HS_CONTROL << 1) | ((_VBO_HS_CONTROL & _BIT1) >> 1)));

    // Set ASY FIFO PLL Tracking Boundary
    ScalerSetBit(P38_08_PLL_TRACKING, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);

    // Set CTS FIFO Initial Address For Reading
    ScalerSetBit(P38_15_CTS_FIFO_H, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);

    // Set CTS FIFO PLL Tracking Boundary
    ScalerSetByte(P38_16_CTS_FIFO_M, 0x11);

    // Set Vby1 Digital Phy Initial
    ScalerSetBit(P38_88_PHY0_TXBIST_00_L1, ~(_BIT4 | _BIT0), (_BIT4 | _BIT0));
    ScalerSetBit(P38_89_PHY0_TXBIST_01_H2, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), _VBO_PN_SWAP);

    // Set Vby1 Analog Phy Initial
    ScalerSetBit(P38_A0_PHY0_APHY_00, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1));
    ScalerSetBit(P38_AD_PHY0_APHY_0D, ~(_BIT5 | _BIT4 | _BIT0), 0x00);

    // Set Vby1 PLL BW setting
    ScalerSetBit(P38_AF_PHY0_APHY_0F, ~_BIT0, 0x00);

    // Set HTPDN control by F/W, pull high
    ScalerDisplayVboHtpdnSetFwControl(_ENABLE);

    // Reset Vby1 Digital Phy, disable Output
    ScalerDisplayVboPhy(_OFF);

    // Reset Vby1 MAC
    ScalerDisplayVboMac(_OFF);

    // Set Vby1 Z0
    ScalerDisplayVboSetZ0();

    // Set Vby1 Driving Control
    ScalerDisplayVboDrivingControl(_VBO_LANE_DRIV_CONTROL, _VBO_PRE_EMPHASIS_CONTROL);

    // Set Vby1 CDR to ALN Latency Control
    ScalerDisplayVboCdr2AlnLatency();

    // LOCKN status initial: Fail
    g_stVboInfo.b1VboLocknStatus = _FAIL;

    // LOCKN Ripped off status initial: False
    g_stVboInfo.b1VboLocknRippedOff = _FALSE;

    // Set Panel Fast Off Disable
    g_stVboInfo.b1PanelFastOffStatus = _DISABLE;
}

//--------------------------------------------------
// Description  : Get Vby1 Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerDisplayGetVboPowerStatus(void)
{
    return (bit)(ScalerGetBit(P38_AD_PHY0_APHY_0D, _BIT7));
}

//--------------------------------------------------
// Description  : Vbyone PLL Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPLL(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up DPLL CLK to Vby1
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, _BIT1);

        // Power Up Vby1 PLL
        ScalerSetBit(P38_AD_PHY0_APHY_0D, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), (_BIT7 | _BIT3));

        // Power Up Vby1 PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, _BIT6);
    }
    else
    {
        // Power Down Vby1 PLL for LCLK
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT6, 0x00);

        // Power Down Vby1 PLL
        ScalerSetBit(P38_AD_PHY0_APHY_0D, ~(_BIT7 | _BIT6 | _BIT3 | _BIT2), 0x00);

        // Disable DPLL CLK to Vby1
        ScalerSetBit(P1_DC_DCLK_GATED_CTRL2, ~_BIT1, 0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust Vbo Ref DPLL Spread Spectrum
// Input Value  : Spread Spectrum Range
// Output Value : None
//--------------------------------------------------
void ScalerDisplaySetVboPLLSSC(bit bDclkSpreadSpeed, BYTE ucSpreadRange)
{
    // The Numbers of Count for Spread Spectrum FMDIV: 30kHz
    ScalerSetByte(P1_D6_DCLK_SSC_COUNT, 0x92);

    // Enable Dclk Spread Range New Mode
    ScalerSetBit(P1_CE_FIXED_LAST_LINE_TRACKING_TIME, ~_BIT6, _BIT6);
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~0xF0, ((ucSpreadRange << 4) & 0xF0));
    ScalerSetBit(P1_C6_DCLK_SPREAD_SPECTRUM, ~_BIT3, (((BYTE)bDclkSpreadSpeed << 3) & _BIT3));
}

//--------------------------------------------------
// Description  : Vbyone Power Control
// Input Value  : _ON or _OFF
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboPower(bit bOn)
{
    if(bOn == _ON)
    {
        // Power Up Vby1 Digital Block: reg_en
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, _BIT7);

        // Power Up Vby1 Analog Block
        ScalerSetBit(P38_A0_PHY0_APHY_00, ~_BIT7, _BIT7);

        // Power Up Vby1 Analog Block
#if(_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)

        // Lane:0 power on
        ScalerSetByte(P38_A1_PHY0_APHY_01, _BIT7);

#elif(_VBO_OUTPUT_PORT == _VBO_2_DATA_LANE)

        // Lane:0-1 power on
        ScalerSetByte(P38_A1_PHY0_APHY_01, (_BIT7 | _BIT6));

#elif(_VBO_OUTPUT_PORT == _VBO_4_DATA_LANE)

        // Lane:0-3 power on
        ScalerSetByte(P38_A1_PHY0_APHY_01, (_BIT7 | _BIT6 | _BIT5 | _BIT4));

#else   // #elif(_VBO_OUTPUT_PORT == _VBO_8_DATA_LANE)

        // Lane:0-7 power on
        ScalerSetByte(P38_A1_PHY0_APHY_01, 0xFF);

#endif  // End of #if(_VBO_OUTPUT_PORT == _VBO_1_DATA_LANE)
    }

    else
    {
        // Power Down Vby1 Analog Block
        ScalerSetByte(P38_A1_PHY0_APHY_01, 0x00);

        // Power Down Vby1 Analog Block
        ScalerSetBit(P38_A0_PHY0_APHY_00, ~_BIT7, 0x00);

        // Power Down Vby1 Digital Block
        ScalerSetBit(P38_09_TRANSMIT_CONTROL_H2, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Settings for Vbyone Z0 Tunning
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDisplayVboSetZ0(void)
{
    // Auto tunning set
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT6, _BIT6);

    // Tunning power on
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT7, _BIT7);

    // Wait for auto trimming stop, time-consuming ~ 1ms
    ScalerTimerDelayXms(2);

    // Tunning power off
    ScalerSetBit(P38_AB_PHY0_APHY_0B, ~_BIT7, 0x00);
}

#endif // #if(_PANEL_STYLE == _PANEL_LVDS)

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
// ID Code      : ScalerGDIPhyTx.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GDIPHYTX__

#include "ScalerFunctionInclude.h"

#if(_DP_TX_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// CODE TABLES
//****************************************************************************
// DPTX Voltage Swing & Pre-emphasis Setting table
//////////////////////////////////////////////////////////////////////////////
///////////////////// DP Standard Voltage Swing table ////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Pre-emphasis->    0            1            2            3
// VoltageSwing
//         0       400mV      400/600mV    400/800mV    420/1200mV
//         1       600mV      600/900mV    610/1210mV       *
//         2       800mV      810mV/1210mV     *            *
//         3       1200mV         *            *            *
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// tDPTX_DRV_TABLE structure
// size = 16 * 3bytes setting
// 3 setting bytes arranged like this
// DEEMPL[7:0]                          first byte
// (DEEMPH[9:8] << 6) | DAT[3:0]        second byte
// (POST1[3:0] << 4) | POST0[3:0]       third byte
//////////////////////////////////////////////////////////////////////////////
// e.g. voltage swing-2 pre-emphasis-1
// DEEMPL[7:0] addr is [(2)*4 + (1)]*3
//////////////////////////////////////////////////////////////////////////////
BYTE code tDPTX_DRV_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x04, 0x40,    0x03, 0x06, 0x42,    0x85, 0x0A, 0x36,    0x0F, 0x0F, 0xF5,
    /*    1    */      0x00, 0x06, 0x42,    0x21, 0x0E, 0x24,    0x1C, 0x0F, 0xFF,    0x1C, 0x0F, 0xFF,
    /*    2    */      0x0C, 0x0D, 0xB3,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,    0x1C, 0x0F, 0xFA,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
};

BYTE code tDPTX_DRV_HBR2_TABLE[48] =
{
    // Pre-emphasis->        0                    1                    2                    3
    // VoltageSwing
    /*    0    */      0x00, 0x03, 0x22,    0x0F, 0x0B, 0x61,    0x0F, 0x0C, 0x5A,    0x63, 0x0F, 0xBE,
    /*    1    */      0x00, 0x05, 0x33,    0x23, 0x0E, 0x67,    0xE0, 0x0F, 0x7F,    0xE0, 0x0F, 0x7F,
    /*    2    */      0x00, 0x07, 0x55,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,    0xE0, 0x0B, 0xFF,
    /*    3    */      0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,    0x00, 0x0F, 0x2D,
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDownStreamInfo g_stDownStreamInfo;
StructDPTxLTInfo g_stTxLTInfo;

//****************************************************************************
// FUNCTION DECLARATIONS
//****************************************************************************
//void ScalerGDIPhyTxMLPowerOn(BYTE ucLaneCnt);
void ScalerGDIPhyTxMLPowerOff(void);
void ScalerGDIPhyTxCMUPowerOn(void);
void ScalerGDIPhyTxCMUPowerOff(void);
void ScalerGDIPhyTxCMUPowerDownMode(void);
//void ScalerGDIPhyTxPHYLaneCntSet(BYTE ucLaneCnt);
void ScalerGDIPhyTxMLPHYSet(void);
void ScalerGDIPhyTxSetSignalLevel(BYTE ucLinkRate, EnumDpTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis);
//void ScalerGDIPhyTxPHYCTS(BYTE ucLinkrate);

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void ScalerGDIPhyTxMLPowerOn(BYTE ucLaneCnt)
{
    // SET Z0 50ohm for Lane 3 and 2
    // [7:4] = 1000 for 50 ohm (Lane3)
    // [3:0] = 1000 for 50 ohm (Lane2)
    ScalerSetByte(PBC_C2_DPTX_Z0_LANE3_2, 0x88);

    // SET Z0 50ohm for Lane 1 and 0
    // [7:4] = 1000 for 50 ohm (Lane1)
    // [3:0] = 1000 for 50 ohm (Lane0)
    ScalerSetByte(PBC_C3_DPTX_Z0_LANE1_0, 0x88);

    // Lane Swap Default Value
    // [7:6] = 00 (Lane0) for Lane0
    // [5:4] = 01 (Lane1) for Lane1
    // [3:2] = 10 (Lane2) for Lane2
    // [1:0] = 11 (Lane3) for Lane3
    // No Lane swap Default value
    ScalerSetByte(PBC_AA_DPTX_SFIFO_LANE_SWAP1, 0x1B);

    // Power Down 4 Lanes
    ScalerSetByte(PBC_A1_DPTX_PHY_CTRL1, 0x0F);

    // Enale DP TX Power and CMU
    // [7] DP TX Power
    // [4] CMU Enable
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT7 | _BIT4),(_BIT7 | _BIT4));

    ScalerGDIPhyTxPHYLaneCntSet(ucLaneCnt);
}
*/

//--------------------------------------------------
// Description  : Dp Tx Main Link Power off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxMLPowerOff(void)
{
    // Power Down 4 Lanes
    ScalerSetByte(PBC_A1_DPTX_PHY_CTRL1, 0x0F);

    // Disable DP TX Power
    // ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
}
/*
//--------------------------------------------------
// Description  : Dp Tx Main Link Lane Cnt Set
// Input Value  : ucLaneCnt 0x00, 0x01, 0x03, 0x0F
//                  Be careful ! not 0, 1, 2, 4
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxPHYLaneCntSet(BYTE ucLaneCnt)
{

    // DP TX power on TX driver
    if(ucLaneCnt == 1)
    {
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);
    }
    else
        if(ucLaneCnt == 2)
        {
            ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT1 | _BIT0));
        }
        else
            if(ucLaneCnt == 4)
            {
                ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));
            }
}
*/
//--------------------------------------------------
// Description  : Dp Tx CMU Power On
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxCMUPowerOn(void)
{
    WORD usNCode = 0;
    WORD usFCode = 0;
    DWORD ulCMUFreq = 5400000;

    // Enable Power of DPTX
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, _BIT7);

    // Enable CMU
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // Wait for CMU Stable
    ScalerTimerDelayXms(2);

    // Disable SSC
    ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    ScalerSetByte(PBC_D2_DPTX_CMU2, 0x00);

    // LDO voltage Setting
    ScalerSetByte(PBC_D3_DPTX_CMU3, 0x55);

    // Set DP mode
    ScalerSetBit(PBC_A9_DPTX_SFIFO_LANE_SWAP0, ~(_BIT7 | _BIT3), _BIT7);

    // Set Small FIFO,half rate (1 bit mode)
    ScalerSetBit(PBC_A7_DPTX_SFIFO_CTRL0, ~(_BIT6 | _BIT5), 0x00);

    // CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
    // Good Phase setting 4'b1111
    ScalerSetByte(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, 0xF0);

    if(GET_DP_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_HBR2)
    {
        // 5.4G
        // HBR2 = 5.4GHz, VCO = 3~6 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), 0x00);

        // VCO = 3 ~ 6GHz,div = 1
        ulCMUFreq = 5400000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));  // VCO 5G~6G

    }
    else if(GET_DP_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_HBR)
    {
        // HBR = 2.7GHz, VCO = 1.5 ~ 3 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // VCO = 1.5 ~ 3GHz, div = 2, 2700000 * 2 = 5400000
        ulCMUFreq = 5400000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G

    }
    else if(GET_DP_TX_DOWNSTREAM_LINK_RATE() == _DP_LINK_RBR)
    {
        // RBR = 1.62GHz, VCO = 1.5 ~ 3 GHz
        ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

        // VCO = 1.5 ~ 3GHz, div = 2, 1620000 * 2 = 3240000
        ulCMUFreq = 3240000;

        // [7] 0:CCO Mode¡B1:VCO Mode
        // [6] 0:Small Kvco¡B1:Big Kvco
        // [5] 0:3rd LPF¡B1:2nd LPF
        // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
        // [3] 0:Use PI¡B1:Bypass PI
        // [2:0] PI Current setting
        ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G
    }

    // Count N.F Code
    usNCode = ulCMUFreq / (_EXT_XTAL * 2) - 4;
    usFCode = ulCMUFreq % (_EXT_XTAL * 2);

    if(usFCode != 0)
    {
        ulCMUFreq = ((DWORD)usFCode << 12);
        usFCode = ulCMUFreq / (_EXT_XTAL * 2);
    }

    // N Code = 9 bit
    // F Code = 12 bit
    usNCode &= 0x1FF;
    usFCode &= 0xFFF;

    // Set N.f code
    // N.f double buffer
    ScalerSetByte(PBC_DF_DPTX_CMU14, (BYTE)usFCode);
    ScalerSetByte(PBC_DE_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    ScalerSetByte(PBC_DD_DPTX_CMU12, (BYTE)(_BIT7 | (usNCode >> 4)));

    // toggle CMU power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // CMU enable
    // Wait PLL stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT7, _BIT7);

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerDelayXms(2);

    // No Weakly Pull-down
    ScalerSetBit(PBC_BC_DPTX_RCVDET_BIAS_PULLDN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);

    // Check PLL is stable or not
    if(ScalerGetBit(PBC_D4_DPTX_CMU4, _BIT7) == 0x00)
    {
        // Disable WD & SSC
        ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);

        // Disable CMU Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

        // Disable DP TX Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
    }

    // Disable WD & SSC
    ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);
}


//--------------------------------------------------
// Description  : Dp Tx CMU Power Off
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxCMUPowerOff(void)
{
    // Check SSC is enable or not
    if(ScalerGetBit(PBC_D5_DPTX_CMU5, _BIT5) != 0x00)
    {
        // Disable SSC
        ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT5, 0x00);

        // SSC Off stable
        ScalerTimerDelayXms(2);
    }

    // Disable CMU Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

    // Disabe DP TX Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Dp Tx CMU Power Down Mode
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxCMUPowerDownMode(void)
{
    SET_DP_TX_DOWNSTREAM_LINK_RATE(_DP_LINK_RBR);

    ScalerGDIPhyTxCMUPowerOn();

    // Preemphasis Level = 0dB
    ScalerSetByte(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, 0x00);
    ScalerSetByte(PBC_B1_DPTX_DEEMP_EN_LANE3L, 0x00);
    ScalerSetByte(PBC_B2_DPTX_DEEMP_EN_LANE2L, 0x00);
    ScalerSetByte(PBC_B3_DPTX_DEEMP_EN_LANE1L, 0x00);
    ScalerSetByte(PBC_B4_DPTX_DEEMP_EN_LANE0L, 0x00);

    // Swing level = lowest swing level
    ScalerSetByte(PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2, 0x00);
    ScalerSetByte(PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0, 0x00);
    ScalerSetByte(PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2, 0x00);
    ScalerSetByte(PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0, 0x00);
    ScalerSetByte(PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2, 0x00);
    ScalerSetByte(PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0, 0x00);

    // Idle Pattern
    ScalerSetByte(PBB_00_DP_PHY_CTRL, 0xFC);
    ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x01);

    // Inter-pair skew enable
    ScalerSetByte(PBB_0D_DPTX_PHY_CTRL, 0x04);

    // Output data
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Power down mode
    ScalerSetByte(PBC_A1_DPTX_PHY_CTRL1, 0x0F);
}


//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3     //Linqian
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxMLPHYSet(void)
{
    switch(GET_DP_TX_DOWNSTREAM_LANE_NUM())
    {
        case _DP_FOUR_LANE:

            // set Lane3 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_3, GET_DP_TX_LANE3_CURRENT_VOL_SWING(), GET_DP_TX_LANE3_CURRENT_PRE_EMPHASIS());

            // set Lane2 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_2, GET_DP_TX_LANE2_CURRENT_VOL_SWING(), GET_DP_TX_LANE2_CURRENT_PRE_EMPHASIS());

            // set Lane1 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());

            // set Lane0 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        case _DP_TWO_LANE:

            // set Lane1 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_1, GET_DP_TX_LANE1_CURRENT_VOL_SWING(), GET_DP_TX_LANE1_CURRENT_PRE_EMPHASIS());

            // set Lane0 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

            break;

        case _DP_ONE_LANE:
        default:

            // set Lane0 PHY voltage swing level
            ScalerGDIPhyTxSetSignalLevel(GET_DP_TX_DOWNSTREAM_LINK_RATE(), _DP_TX_LANE_0, GET_DP_TX_LANE0_CURRENT_VOL_SWING(), GET_DP_TX_LANE0_CURRENT_PRE_EMPHASIS());

            break;
    }
}

//--------------------------------------------------
// Description  : Dp Tx ML set VoltageSwing and PreEmphasis
// Input Value  : LaneX - 0~3 VoltageSwing - 0~3 PreEmphasis - 0~3
// Output Value :
//--------------------------------------------------
void ScalerGDIPhyTxSetSignalLevel(BYTE ucLinkRate, EnumDpTxLane enumLaneX, BYTE ucVoltageSwing, BYTE ucPreEmphasis)
{
    BYTE ucIndex = 0x00;
    BYTE *pucTable = 0x00;

    // Protect Wrong table
    if(ucVoltageSwing + ucPreEmphasis > 3)
    {
        if(ucVoltageSwing < 4)
        {
            ucPreEmphasis = 3 - ucVoltageSwing;
        }
        else
        {
            ucVoltageSwing = 3;
            ucPreEmphasis = 0;
        }
    }


    ucIndex = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;

    if(ucLinkRate == _DP_LINK_HBR2)
    {
        pucTable = tDPTX_DRV_HBR2_TABLE;
    }
    else
    {
        pucTable = tDPTX_DRV_TABLE;
    }

    switch(enumLaneX)
    {
        case _DP_TX_LANE_0:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x03, ((pucTable[ucIndex + 1] & 0xF0) >> 4));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B4_DPTX_DEEMP_EN_LANE0L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] >> 4));

            // Post0 [3:0]
            ScalerSetBit(PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DP_TX_LANE_1:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x0C, ((pucTable[ucIndex + 1] & 0xF0) >> 2));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B3_DPTX_DEEMP_EN_LANE1L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B7_DPTX_DRV_DAC_DAT_LANE1_0, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(PBC_BB_DPTX_DRV_DAC_POST1_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(PBC_B9_DPTX_DRV_DAC_POST0_LANE1_0, ~0xF0, (pucTable[ucIndex + 2] << 4));

            break;

        case _DP_TX_LANE_2:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0x30, ((pucTable[ucIndex + 1] & 0xF0) >> 0));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B2_DPTX_DEEMP_EN_LANE2L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0x0F, (pucTable[ucIndex + 1] & 0x0F));

            // Post1 [3:0]
            ScalerSetBit(PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] >> 4));

            // Post0 [3:0]
            ScalerSetBit(PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2, ~0x0F, (pucTable[ucIndex + 2] & 0x0F));

            break;

        case _DP_TX_LANE_3:

            // De-emphasis [9:8]
            ScalerSetBit(PBC_B0_DPTX_DEEMP_EN_LANE3_0H, ~0xC0, ((pucTable[ucIndex + 1] & 0xF0) << 2));

            // De-emphasis [7:0]
            ScalerSetByte(PBC_B1_DPTX_DEEMP_EN_LANE3L, pucTable[ucIndex + 0]);

            // Data [3:0]
            ScalerSetBit(PBC_B6_DPTX_DRV_DAC_DAT_LANE3_2, ~0xF0, ((pucTable[ucIndex + 1] & 0x0F) << 4));

            // Post1 [3:0]
            ScalerSetBit(PBC_BA_DPTX_DRV_DAC_POST1_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] & 0xF0));

            // Post0 [3:0]
            ScalerSetBit(PBC_B8_DPTX_DRV_DAC_POST0_LANE3_2, ~0xF0, (pucTable[ucIndex + 2] << 4));

            break;

        default:

            // No data
            break;
    }
}


//--------------------------------------------------
// Description  : Dp Tx Main Link Power on
// Input Value  :
// Output Value :
//--------------------------------------------------
/*
void ScalerGDIPhyTxPHYCTS(BYTE ucLinkrate)
{

    WORD usNCode = 0;
    WORD usFCode = 0;
    DWORD ulCMUFreq = 0;

    //////////////////////////
    //Analog Model Setting ///
    //////////////////////////

    // Select PLL Clk reference for DP
    ScalerSetBit(PBC_A9_DPTX_SFIFO_LANE_SWAP0, ~_BIT3, 0x00);

    // Select FIFO data source from DP
    ScalerSetBit(PBC_A9_DPTX_SFIFO_LANE_SWAP0, ~_BIT7, _BIT7);

    // Enable  Tx Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, _BIT7);

    // LDO Voltage
    ScalerSetByte(PBC_D3_DPTX_CMU3, 0x55);

    // Enable CMU Power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // Duty cycle of CLKRD clock
    ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (_BIT7 | _BIT6 | _BIT5 | _BIT4));

    // Enable DPTX Lanes
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT1 | _BIT0));

    // Lane Swap
    ScalerSetByte(PBC_AA_DPTX_SFIFO_LANE_SWAP1, 0xE4);

    switch(ucLinkrate)
    {
        case _DP_LINK_HBR2:

            // 5.4G
            // HBR2 = 5.4GHz, VCO = 3~6 GHz
            ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), 0x00);

            // VCO = 3 ~ 6GHz,div = 1
            ulCMUFreq = 5400000;

            // [7] 0:CCO Mode¡B1:VCO Mode
            // [6] 0:Small Kvco¡B1:Big Kvco
            // [5] 0:3rd LPF¡B1:2nd LPF
            // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
            // [3] 0:Use PI¡B1:Bypass PI
            // [2:0] PI Current setting
            ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

            // [6:4] CMU'S LPF Rs
            // [3:0] CMU'S CP Current
            ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2| _BIT1));  // VCO 5G~6G

            break;

        case _DP_LINK_HBR:

            // HBR = 2.7GHz, VCO = 1.5 ~ 3 GHz
            ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

            // VCO = 1.5 ~ 3GHz, div = 2, 2700000 * 2 = 5400000
            ulCMUFreq = 5400000;

            // [7] 0:CCO Mode¡B1:VCO Mode
            // [6] 0:Small Kvco¡B1:Big Kvco
            // [5] 0:3rd LPF¡B1:2nd LPF
            // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
            // [3] 0:Use PI¡B1:Bypass PI
            // [2:0] PI Current setting
            ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

            // [6:4] CMU'S LPF Rs
            // [3:0] CMU'S CP Current
            ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G

            break;

    case _DP_LINK_RBR:

            // RBR = 1.62GHz, VCO = 1.5 ~ 3 GHz
            ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

            // VCO = 1.5 ~ 3GHz, div = 2, 1620000 * 2 = 3240000
            ulCMUFreq = 3240000;

            // [7] 0:CCO Mode¡B1:VCO Mode
            // [6] 0:Small Kvco¡B1:Big Kvco
            // [5] 0:3rd LPF¡B1:2nd LPF
            // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
            // [3] 0:Use PI¡B1:Bypass PI
            // [2:0] PI Current setting
            ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

            // [6:4] CMU'S LPF Rs
            // [3:0] CMU'S CP Current
            ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G

            break;

     default:

            // RBR = 1.62GHz, VCO = 1.5 ~ 3 GHz
            ScalerSetBit(PBC_BD_DPTX_CKRDDUTY_SPD_SEL, ~(_BIT1 | _BIT0), _BIT0);

            // VCO = 1.5 ~ 3GHz, div = 2, 1620000 * 2 = 3240000
            ulCMUFreq = 3240000;

            // [7] 0:CCO Mode¡B1:VCO Mode
            // [6] 0:Small Kvco¡B1:Big Kvco
            // [5] 0:3rd LPF¡B1:2nd LPF
            // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
            // [3] 0:Use PI¡B1:Bypass PI
            // [2:0] PI Current setting
            ScalerSetBit(PBC_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

            // [6:4] CMU'S LPF Rs
            // [3:0] CMU'S CP Current
            ScalerSetBit(PBC_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));  // VCO 3G~4G

            break;

    }

    // Count N.F Code
    usNCode = ulCMUFreq / (_EXT_XTAL * 2) - 4;
    usFCode = ulCMUFreq % (_EXT_XTAL * 2);

    if(usFCode != 0)
    {
        ulCMUFreq = ((DWORD)usFCode << 12);
        usFCode = ulCMUFreq / (_EXT_XTAL * 2);
    }

    // N Code = 9 bit
    // F Code = 12 bit
    usNCode &= 0x1FF;
    usFCode &= 0xFFF;

    // Set N.f code
    ScalerSetByte(PBC_DD_DPTX_CMU12, (BYTE)(usNCode >> 4));
    ScalerSetByte(PBC_DE_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    ScalerSetByte(PBC_DF_DPTX_CMU14, (BYTE)usFCode);

    // N.f double buffer
    ScalerSetBit(PBC_DD_DPTX_CMU12, ~_BIT7, _BIT7);

    // toggle CMU power
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);
    ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // CMU enable
    // Wait PLL stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    ScalerSetBit(PBC_D5_DPTX_CMU5, ~_BIT7, _BIT7);    // Enable WD

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerDelayXms(2);

    // Check PLL is stable or not
    if(ScalerGetBit(PBC_D4_DPTX_CMU4, _BIT7) == 0x00)
    {
        // Disable WD & SSC
        ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);

        // Disable CMU Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

        // Disable DP TX Power
        ScalerSetBit(PBC_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
    }

    // Disable WD & SSC
    ScalerSetByte(PBC_D5_DPTX_CMU5, 0x00);

    // PRBS 7 Pattern
    ScalerSetByte(PBB_01_DPTX_ML_PAT_SEL, 0x55);

    // Double buffer
    ScalerSetBit(PBB_01_DPTX_ML_PAT_SEL, ~(_BIT1 | _BIT0), _BIT0);

    // Disable Power-Down
    ScalerSetByte(PBC_A1_DPTX_PHY_CTRL1, 0x00);
}
*/
#endif // End of #if(_DP_TX_SUPPORT == _ON)


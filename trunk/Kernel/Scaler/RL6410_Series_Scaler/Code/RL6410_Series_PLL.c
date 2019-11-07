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
// ID Code      : RL6410_Series_PLL.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_LVDS)

//--------------------------------------------------
// Definations of LVDS VCO Range, convert into Dclk frequency
//--------------------------------------------------
#define _LVDS_PLL_BOUNDRY_0                         (250000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_1                         (500000  * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))
#define _LVDS_PLL_BOUNDRY_2                         (1000000 * (1 << _LVDS_OUTPUT_PORT) / (7 << _D_DOMAIN_PATH))

#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
//--------------------------------------------------
// Definations of DPTX CLK Into DPLL Range
//--------------------------------------------------
#define _DPTX_CLK_IN_BOUNDRY_0                      56000
#define _DPTX_CLK_IN_BOUNDRY_1                      112000
#define _DPTX_CLK_IN_BOUNDRY_2                      224000

//--------------------------------------------------
// Definations of DPTX CMU CCO Range
//--------------------------------------------------
#define _DPTX_PLL_BOUNDRY_0                         750000
#define _DPTX_PLL_BOUNDRY_1                         1500000
#define _DPTX_PLL_BOUNDRY_2                         2000000
#define _DPTX_PLL_BOUNDRY_3                         3000000

#if(_PANEL_STYLE == _PANEL_DPTX)
#define _DPTX_PHY_RATE_RBR                          1620000
#define _DPTX_PHY_RATE_HBR                          2700000
#define _DPTX_PHY_RATE_HBR2                         5400000
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)

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
#if(_PANEL_STYLE == _PANEL_DPTX)
bit ScalerPLLGetDptxPowerStatus(void);
#endif
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq);

#if(_PANEL_STYLE == _PANEL_LVDS)
void ScalerPLLSetDisplayPLL(DWORD ulFreq);
#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
void ScalerPLLSetDPLLRefPLL(DWORD ulFreq);
void ScalerPLLDPTxPLLReset(void);
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
//--------------------------------------------------
// Description  : Get Dptx Power Status
// Input Value  : None
// Output Value : _TRUE: Power On   _FALSE: Power Down
//--------------------------------------------------
bit ScalerPLLGetDptxPowerStatus(void)
{
    return (bit)(ScalerGetBit(P38_A0_DPTX_PHY_CTRL0, _BIT4));
}
#endif // End of #if(_PANEL_STYLE == _PANEL_DPTX)

//--------------------------------------------------
// Description  : Get DPLL Ref Clk from DPTx PLL or Xtal
// Input Value  : Dclk
// Output Value : DPTx PLL clk or Xtal Clk
//--------------------------------------------------
DWORD ScalerPLLGetDPLLRefClk(DWORD ulFreq)
{
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
    DWORD ulMacClk = 0;
    DWORD ulDPTxClkIn = 0;
#endif

    ulFreq = ulFreq;

#if(_PANEL_STYLE == _PANEL_VBO)

    ulMacClk = (ulFreq * _VBO_BYTE_MODE) / _VBO_OUTPUT_PORT;

#elif(_PANEL_STYLE == _PANEL_DPTX)

    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR)
    {
        ulMacClk = _DPTX_PHY_RATE_RBR / 10;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR)
    {
        ulMacClk = _DPTX_PHY_RATE_HBR / 10;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        ulMacClk = _DPTX_PHY_RATE_HBR2 / 10;
    }

#endif // End of #if(_PANEL_STYLE == _PANEL_VBO)

#if((_PANEL_STYLE == _PANEL_LVDS) || (_PANEL_STYLE == _PANEL_DPTX))

    ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT1), 0x00);

    return (_EXT_XTAL);

#elif(_PANEL_STYLE == _PANEL_VBO)

    ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT1), _BIT1);

    if(ulMacClk > _DPTX_CLK_IN_BOUNDRY_2)
    {
        ulDPTxClkIn = ulMacClk / 16;
        ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT3 | _BIT2), (_BIT3 | _BIT2));
    }
    else if(ulMacClk > _DPTX_CLK_IN_BOUNDRY_1)
    {
        ulDPTxClkIn = ulMacClk / 8;
        ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT3 | _BIT2), (_BIT3));
    }
    else if(ulMacClk > _DPTX_CLK_IN_BOUNDRY_0)
    {
        ulDPTxClkIn = ulMacClk / 4;
        ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT3 | _BIT2), (_BIT2));
    }
    else
    {
        ulDPTxClkIn = ulMacClk / 2;
        ScalerSetBit(P1_D8_DPLL_RELOAD_CTRL, ~(_BIT3 | _BIT2), 0x00);
    }

    return (ulDPTxClkIn);

#endif // End of #if((_PANEL_STYLE == _PANEL_LVDS) || (_PANEL_STYLE == _PANEL_DPTX))

    return (_EXT_XTAL);
}

#if(_PANEL_STYLE == _PANEL_LVDS)
//--------------------------------------------------
// Description  : Set Display Interface PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDisplayPLL(DWORD ulFreq)
{
    BYTE ucDispPllParam = 0x00;

    PDATA_DWORD(0) = (ulFreq >> _D_DOMAIN_PATH) * 16 / 15;

    // ----------- Previous Select Band & Div Alg. -----------
    // ucDispPllParam: [7:6] = LVDS_PLL_VCO
    if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_0)
    {
        ucDispPllParam |= (3 << 6);
    }
    else if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_1)
    {
        ucDispPllParam |= (2 << 6);
    }
    else if(PDATA_DWORD(0) < _LVDS_PLL_BOUNDRY_2)
    {
        ucDispPllParam |= (1 << 6);
    }
    else
    {
        ucDispPllParam |= (0 << 6);
    }

    // LVDS data rate = ((Pixel Clk) / (LVDS Outport)) * 7
    PDATA_DWORD(1) = ((PDATA_DWORD(0) << _D_DOMAIN_PATH) / (1 << _LVDS_OUTPUT_PORT)) * 7;

    // ucDispPllParam: [3:2] = LVDS PI Operation Frequency Seletcion
    if(PDATA_DWORD(1) < 250000)
    {
        ucDispPllParam |= (0 << 2);
    }
    else if(PDATA_DWORD(1) < 400000)
    {
        ucDispPllParam |= (1 << 2);
    }
    else if(PDATA_DWORD(1) < 600000)
    {
        ucDispPllParam |= (2 << 2);
    }
    else
    {
        ucDispPllParam |= (3 << 2);
    }

    // ----------- Set Display VCO Band -----------
    // Manual set LVDS VCO band
    ScalerDisplayLvdsSetVcoBand((ucDispPllParam & 0xC0) >> 6);

    // Set LVDS PI Operation band
    ScalerDisplayLvdsSetPhaseBand(((ucDispPllParam & 0x0C) >> 2) << 5);
}

#elif((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
//--------------------------------------------------
// Description  : Set DPLL Referenced DPTX PLL: Frequency, VCO Band
// Input Value  : Target Freq
// Output Value : None
//--------------------------------------------------
void ScalerPLLSetDPLLRefPLL(DWORD ulFreq)
{
    WORD usNCode = 0;
    WORD usFCode = 0;
    DWORD ulCMUFreq = 0;

#if(_PANEL_STYLE == _PANEL_VBO)

    ulCMUFreq = (ulFreq * _VBO_BYTE_MODE * 10) / _VBO_OUTPUT_PORT;

    // Set Center SSC
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT6, _BIT6);

    if(ScalerGetBit(P38_A0_DPTX_PHY_CTRL0, _BIT4) == 0x00)
    {
        // Disable SSC Function
        ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);
    }

#elif(_PANEL_STYLE == _PANEL_DPTX)

    if(ScalerGetBit(P38_A0_DPTX_PHY_CTRL0, _BIT4) == _BIT4)
    {
        return;
    }

    ulFreq = ulFreq;

    // HBR2 = 5.4GHz, HBR = 2.7GHz, RBR = 1.62GHz
    if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_RBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_RBR;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR;
    }
    else if(_PANEL_DPTX_LINK_RATE == _PANEL_DPTX_LINK_HBR2)
    {
        ulCMUFreq = _DPTX_PHY_RATE_HBR2;
    }

    // Set Down SSC
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT6, 0x00);

    // Disable SSC Function
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);

#endif

    // Enable Power of DPTX
    ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT7, _BIT7);

    // Divider for Postdivider of CMU and Pre-divder of CMU
    ScalerSetBit(P38_D2_DPTX_CMU2, ~(_BIT4 | _BIT1 | _BIT0), 0x00);

    // LDO voltage Setting
    ScalerSetBit(P38_D3_DPTX_CMU3, ~(_BIT6 | _BIT5 | _BIT4 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT4 | _BIT2 | _BIT0));

    // CLKRD duty set to 4'b1111 @0638 as AMlee suggests.
    // Good Phase setting H/L = 4/6
    ScalerSetBit(P38_C2_DPTX_CKRDDUTY_SPD_SEL0, ~0xFF, 0xFF);

    // [7] 0:CCO Mode¡B1:VCO Mode
    // [6] 0:Small Kvco¡B1:Big Kvco
    // [5] 0:3rd LPF¡B1:2nd LPF
    // [4] 0:1pF¡B1:2pF (CMU'S LPF Cp)
    // [3] 0:Use PI¡B1:Bypass PI
    // [2:0] PI Current setting
    ScalerSetBit(P38_D0_DPTX_CMU0, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0));

    if(ulCMUFreq > _DPTX_PLL_BOUNDRY_3)
    {
        // Phy range = 3~6 GHz
        ulCMUFreq = ulCMUFreq;

        // VCO = 3~6 GHz, spdsel = div1
        ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), 0x00);

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(P38_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_2)
    {
        // Phy range = 1.5 ~ 3 GHz
        ulCMUFreq = ulCMUFreq * 2;

        // VCO = 3~6 GHz, spdsel = div2
        ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), _BIT0);

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(P38_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_1)
    {
        // Phy range = 1.5 ~ 3 GHz
        ulCMUFreq = ulCMUFreq * 2;

        // VCO = 3~6 GHz, spdsel = div2
        ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), _BIT0);

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(P38_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
    }
    else if(ulCMUFreq > _DPTX_PLL_BOUNDRY_0)
    {
        // Phy range = 0.75 ~ 1.5 GHz
        ulCMUFreq = ulCMUFreq * 4;

        // VCO = 3~6 GHz, spdsel = div4
        ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), _BIT1);

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(P38_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
    }
    else
    {
        // VCO = 375 ~ 750 MHz
        ulCMUFreq = ulCMUFreq * 8;

        // VCO = 3~6 GHz, spdsel = div8
        ScalerSetBit(P38_C3_DPTX_CKRDDUTY_SPD_SEL1, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));

        // [6:4] CMU'S LPF Rs
        // [3:0] CMU'S CP Current
        ScalerSetBit(P38_D1_DPTX_CMU1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT4 | _BIT2));
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

    ScalerSetByte(P38_DE_DPTX_CMU14, (BYTE)usFCode);
    ScalerSetByte(P38_DD_DPTX_CMU13, ((BYTE)(usNCode << 4) | (BYTE)(usFCode >> 8)));
    ScalerSetByte(P38_DC_DPTX_CMU12, (BYTE)(_BIT7 | (usNCode >> 4)));

    // Enable CMU power
    ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT4, _BIT4);

    // Wait for CMU Stable
    ScalerTimerDelayXms(2);

    // Enable Watch Dog
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT7, _BIT7);

    // Wait Watch Dog to check PLL is stable or not
    ScalerTimerPollingFlagProc(2, P38_D4_DPTX_CMU4, _BIT7, _TRUE);

    // Disable WD
    ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT7, 0x00);
}

//--------------------------------------------------
// Description  : Reset DPTX PLL Setting, Disable DPTX PLL Spread Spectrum Output
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerPLLDPTxPLLReset(void)
{
    // Check SSC is enable or not
    if(ScalerGetBit(P38_D5_DPTX_CMU5, _BIT5) != 0x00)
    {
        // Disable SSC
        ScalerSetBit(P38_D5_DPTX_CMU5, ~_BIT5, 0x00);

        // SSC Off stable
        ScalerTimerDelayXms(2);
    }

    // Disable CMU Power
    ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT4, 0x00);

    // Disabe DP TX Power
    ScalerSetBit(P38_A0_DPTX_PHY_CTRL0, ~_BIT7, 0x00);
}
#endif // End of #if(_PANEL_STYLE == _PANEL_LVDS)
